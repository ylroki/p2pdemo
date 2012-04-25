#include "task_find_node.h"
#include "kad.h"
#include "route_table.h"
#include "define.h"
CTaskFindNode::CTaskFindNode(CKad* kad, CUInt128 id)
	:CTask(kad),
	m_NodeID(id),
	m_Status(FNS_INIT)
{
	m_Possible.clear();
	m_PossibleStatus.clear();
	m_Trying.clear();
}

CTaskFindNode::~CTaskFindNode()
{}

void CTaskFindNode::Update()
{
	switch (m_Status)
	{
	case FNS_INIT:
		{
			std::list<TNode> nodes;
			m_Kad->GetRouteTable()->GetCloseTo(m_NodeID, &nodes);
			std::list<TNode>::iterator it;
			for (it = nodes.begin(); it != nodes.end(); ++it)
			{
				CUInt128 distance = it->NodeID ^ m_NodeID;
				m_Possible.insert(std::make_pair(distance, *it));
				m_PossibleStatus.insert(std::make_pair(distance, RNS_PENDING));
			}
			m_Status = FNS_UPDATE;
			break;
		}
	case FNS_UPDATE:
		{
			if (CheckStatus() == true)//if all ok, CheckStatus() return true.
			{
				//TODO
				m_Status = FNS_END;
				break;
			}
			break;
		}
	case FNS_END:
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

void CTaskFindNode::Process(void* arg)
{
	std::list<TNode>* nodes;
	std::list<TNode>::iterator it;
	//The front node is remote node.
	TNode remote = nodes->front();
	nodes->pop_front();
	std::map<CUInt128, KRemoteNodeStatus>::iterator itStatus;
	itStatus = m_PossibleStatus.find(remote.NodeID^m_NodeID);
	if (itStatus != m_PossibleStatus.end())
		itStatus->second = RNS_OK;

 	//The rest are nodes remote responsed.
	for (it = nodes->begin(); it != nodes->end(); ++it)
	{
		CUInt128 distance = it->NodeID ^ m_NodeID;
		m_Possible.insert(std::make_pair(distance, *it));
		m_PossibleStatus.insert(std::make_pair(distance, RNS_PENDING));
	}
}

bool CTaskFindNode::CheckStatus()
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
				SendMessage(it->first);
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

void CTaskFindNode::SendMessage(CUInt128 distance)
{
	//TODO
}
