#include "task_find_node.h"
#include "kad.h"
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
				m_Possible.insert(make_pair(it->NodeID, *it));
				m_PossibleStatus.insert(make_pair(it->NodeID, RNS_PENDING));
			}
			m_Status = FNS_UPDATE;
			break;
		}
	case FNS_UPDATE:
		{
			//TODO
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
	//TODO
}
