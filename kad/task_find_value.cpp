#include "task_find_value.h"
#include "kad.h"
#include "lookup.h"

CTaskFindValue::CTaskFindValue(CKad* kad, CUInt128 key)
	:CTask(kad),
	m_Key(key)
{}

CTaskFindValue::~CTaskFindValue()
{}

void CTaskFindValue::Update()
{
	switch (m_Status)
	{
	case FVS_INIT:
		{
			m_Lookup->Init();	
			m_Status = FVS_UPDATE;
			break;
		}
	case FVS_UPDATE:
		{
			if (m_Lookup->CheckStatus(0x46) == true)//if all ok, CheckStatus() return true.
			{
				m_Status = FVS_END;
				break;
			}
			break;
		}
	case FVS_END:
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

void CTaskFindValue::Process(void* arg)
{
	if (arg == NULL)
	{
		m_Status = FVS_END;
		return;
	}
	std::list<TNode>* nodes = static_cast<std::list<TNode>*>(arg);
	m_Lookup->ProcessNodes(nodes);	
}
