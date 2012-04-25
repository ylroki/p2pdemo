#include "task_simple_store.h"
#include "task.h"
#include "kad.h"
#include "route_table.h"
CTaskSimpleStore::CTaskSimpleStore(CKad* kad, std::string md5, 
	unsigned long ip, unsigned short port, unsigned long size)
	:CTask(kad),
	m_IPv4(ip),
	m_Port(port),
	m_Size(size),
	m_Status(SSS_INIT)
{
	m_Key = CUInt128::FromMD5(md5.c_str());
}

CTaskSimpleStore::~CTaskSimpleStore()
{}

void CTaskSimpleStore::Update()
{
	switch (m_Status)
	{
	case SSS_INIT:
		{
			m_CloseNode.clear();
			m_Kad->GetRouteTable()->GetCloseTo(m_Key, &m_CloseNode);
			m_Status = SSS_UPDATE;
			break;
		}
	case SSS_UPDATE:
		{
			if (m_CloseNode.size() > 0)
			{
				TNode node = m_CloseNode.front();
				m_CloseNode.pop_front();
				char buf[BUF_SIZE];
				CMemoryStream sender(buf, 0, BUF_SIZE);
				sender.WriteInteger<char>(0x42);
				unsigned char hex[16];
				m_Kad->GetClientIDHex(hex);
				sender.WriteBuffer(hex, 16);
				m_Key.ToHex(hex);
				sender.WriteBuffer(hex, 16);
				sender.WriteInteger<unsigned long>(htonl(m_IPv4));
				sender.WriteInteger<unsigned short>(htons(m_Port));
				sender.WriteInteger<unsigned long>(htonl(m_Size));

				SendTo(m_Kad->GetSocket(), buf, sender.GetSize(), node.IPv4.c_str(), node.Port);
			}
			else
			{
				m_Status = SSS_END;
			}
			break;
		}
	case SSS_END:
		{
			m_IsStopped = true;
			break;
		}
	default:
		{
			break;
		}
	}
}

void CTaskSimpleStore::Process(void* arg)
{
}


