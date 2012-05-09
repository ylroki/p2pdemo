#include "task_ping.h"
#include "kad.h"
#include "route_table.h"
#include "uint128.h"
#include "stream.h"
#include "socket_header.h"

CTaskPing::CTaskPing(CKad* kad, TNode& node)
	:CTask(kad),
	m_Status(PS_INIT)
{
	m_Node = new TNode;
	m_Node->NodeID = node.NodeID;
	m_Node->IPv4 = node.IPv4;
	m_Node->Port = node.Port;
}

CTaskPing::~CTaskPing()
{
	if (m_Node)
		delete m_Node;
}

void CTaskPing::Update()
{
	static int nTry = 3;
	switch (m_Status)
	{
	case PS_INIT:
		{
			char buf[BUF_SIZE];
			CMemoryStream sender(buf, 0, BUF_SIZE);
			sender.WriteInteger<char>(0x40);
			unsigned char hex[16];
			m_Kad->GetClientIDHex(hex);
			sender.WriteBuffer(hex, 16);
			sender.WriteInteger<short>(htons(m_TaskID));
			SendTo(m_Kad->GetSocket(), buf, sender.GetSize(), m_Node->IPv4.c_str(), m_Node->Port);
			m_Status = PS_WAIT;
			break;
		}
	case PS_WAIT:
		{
			time_t now = GetNowSeconds();
			if (now - m_Start >= m_Timeout)
			{
				// time out.
				m_Kad->GetRouteTable()->Delete(m_Node->NodeID);
				if (nTry--)
					m_Status = PS_INIT;
				else
					m_Status = PS_END;
			}
			break;
		}
	case PS_END:
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

void CTaskPing::Process(void* arg)
{
	if (m_Status == PS_WAIT)
		m_Status = PS_END;
}
