#include "task_find_node.h"
#include "kad.h"
#include "lookup.h"

CTaskFindNode::CTaskFindNode(CKad* kad, CUInt128 id)
	:CTask(kad),
	m_NodeID(id),
	m_Status(FNS_INIT)
{
	m_Lookup = new CLookup(kad, id, this);
}

CTaskFindNode::~CTaskFindNode()
{
	delete m_Lookup;
}

void CTaskFindNode::Update()
{
	switch (m_Status)
	{
	case FNS_INIT:
		{
			m_Lookup->Init();	
			m_Status = FNS_UPDATE;
			break;
		}
	case FNS_UPDATE:
		{
			if (m_Lookup->CheckStatus() == true)//if all ok, CheckStatus() return true.
			{
				if (m_CallbackFunc)
					m_CallbackFunc(m_Caller, m_CallbackArg);
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
	std::list<TNode>* nodes = static_cast<std::list<TNode>*>(arg);
	m_Lookup->ProcessNodes(nodes);	
}

