#include "lookup.h"
#include "kad.h"
#include "route_table.h"
#include "define.h"
#include "socket_header.h"
#include "task.h"

CLookup::CLookup(CKad* kad, CUInt128 target, CTask* task)
	:m_Kad(kad),
	m_Target(target),
	m_Task(task)
{
	m_Possible.clear();
	m_PossibleStatus.clear();
	m_Trying.clear();
}

CLookup::~CLookup()
{}

void CLookup::Init()
{
	std::list<TNode> nodes;
	m_Kad->GetRouteTable()->GetCloseTo(m_Target, &nodes);
	std::list<TNode>::iterator it;
	for (it = nodes.begin(); it != nodes.end(); ++it)
	{
		CUInt128 distance = it->NodeID ^ m_Target;
		m_Possible.insert(std::make_pair(distance, *it));
		m_PossibleStatus.insert(std::make_pair(distance, RNS_PENDING));
	}
}

bool CLookup::CheckStatus(char cmd)
{
	std::map<CUInt128, KRemoteNodeStatus>::iterator it;
	int nTry = 0;
	bool allOK = true;
	for (it = m_PossibleStatus.begin(); it != m_PossibleStatus.end(); ++it)
	{
		switch (it->second)
		{
		case RNS_PENDING:
			{
				allOK = false;
				time_t now = GetNowSeconds();
				m_Trying.insert(std::make_pair(it->first, now+10));
				it->second = RNS_TRYING;
				SendMessage(cmd, it->first);
				++nTry;
				if (nTry >= KAD_ALPHA)
					return false;
				break;
			}
		case RNS_TRYING:
			{
				allOK = false;
				std::map<CUInt128, time_t>::iterator itTry = m_Trying.find(it->first);
				if (itTry != m_Trying.end())
				{
					time_t now = GetNowSeconds();
					if (now >= itTry->second)
					{	
						m_Trying.erase(itTry);
						it->second = RNS_TIMEOUT;
					}
				}
				break;
			}
		case RNS_OK:
			{
				break;
			}
		case RNS_TIMEOUT:
			{
				break;
			}
		default:
			{
				break;
			}
		}
	}
	return allOK;
}

void CLookup::SendMessage(char cmd, CUInt128 distance)
{
	std::map<CUInt128, TNode>::iterator it = m_Possible.find(distance);
	if (it != m_Possible.end())
	{
		TNode node = it->second;
		char buf[BUF_SIZE];
		CMemoryStream sender(buf, 0, BUF_SIZE);
		sender.WriteInteger<char>(cmd);
		unsigned char hex[16];
		m_Kad->GetClientIDHex(hex);
		sender.WriteBuffer(hex, 16);
		sender.WriteInteger<short>(htons(m_Task->GetTaskID()));
		m_Target.ToHex(hex);//node id or key
		sender.WriteBuffer(hex, 16);
		SendTo(m_Kad->GetSocket(), buf, sender.GetSize(), node.IPv4.c_str(), node.Port);
	}
}

void CLookup::ProcessNodes(std::list<TNode>* nodes)
{
	std::list<TNode>::iterator it;
	//The front node is remote node.
	TNode remote = nodes->front();
	nodes->pop_front();
	std::map<CUInt128, KRemoteNodeStatus>::iterator itStatus;
	itStatus = m_PossibleStatus.find(remote.NodeID^m_Target);
	if (itStatus != m_PossibleStatus.end())
		itStatus->second = RNS_OK;

 	//The rest are nodes remote responsed.
	for (it = nodes->begin(); it != nodes->end(); ++it)
	{
		CUInt128 distance = it->NodeID ^ m_Target;
		m_Possible.insert(std::make_pair(distance, *it));
		m_PossibleStatus.insert(std::make_pair(distance, RNS_PENDING));
	}
}
