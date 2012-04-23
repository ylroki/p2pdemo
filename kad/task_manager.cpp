#include "task_manager.h"
CTask::CTask()
	:m_Timeout(600000),//10 min
	m_TaskID(-1),
	m_IsStopped(false)
{}

CTask::~CTask()
{}

void CTask::SetTimeout(time_t millisec)
{
	m_Timeout = millisec;
}

void CTask::SetTaskID(short id)
{
	m_TaskID = id;
}

short CTask::GetTaskID()
{
	return m_TaskID;
}

bool CTask::IsStopped()
{
	return m_IsStopped;
}

CTaskSimpleStore::CTaskSimpleStore(std::string md5, unsigned long ip, unsigned short port)
	:m_IPv4(ip),
	m_Port(port)
{
	m_Key = CUInt128::FromMD5(md5.c_str());
}

CTaskSimpleStore::~CTaskSimpleStore()
{}

void CTaskSimpleStore::Update()
{
	//TODO
	printf("simple store\n");
}


CTaskPing::CTaskPing(TNode& node)
{
	TNode* m_Node = new TNode;
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
	//TODO
	printf("ping\n");
}

CTaskFindNode::CTaskFindNode(CUInt128 id)
	:m_NodeID(id)
{
}

CTaskFindNode::~CTaskFindNode()
{}

void CTaskFindNode::Update()
{
	//TODO
	printf("find node\n");
}

CTaskFindValue::CTaskFindValue(CUInt128 key)
	:m_Key(key)
{}

CTaskFindValue::~CTaskFindValue()
{}

void CTaskFindValue::Update()
{
	//TODO
	printf("find value\n");
}

CTaskManager::CTaskManager()
	:m_TaskID(),
	m_Lock()
{
	m_ListTask.clear();
	m_ListPending.clear();
}

CTaskManager::~CTaskManager()
{
	std::list<CTask*>::iterator it;
	for (it = m_ListTask.begin(); it != m_ListTask.end(); ++it)
		delete (*it);
	for (it = m_ListPending.begin(); it != m_ListPending.end(); ++it)
		delete (*it);
}

void CTaskManager::Add(CTask* task)
{
	CAutoLock autolock(&m_Lock);
	short taskID = m_TaskID.New();
	if (taskID < 0)
	{
		m_ListPending.push_back(task);
		return;
	}
	task->SetTaskID(taskID);
	m_ListTask.push_back(task);
}

void CTaskManager::Update()
{
	CAutoLock autolock(&m_Lock);
	while (m_ListPending.size() > 0)
	{
		short taskID = m_TaskID.New();
		if (taskID < 0)
			break;
		CTask* task = m_ListPending.front();
		m_ListPending.pop_front();
		task->SetTaskID(taskID);
		m_ListTask.push_back(task);
	}
	
	std::list<CTask*>::iterator it;
	for (it = m_ListTask.begin(); it != m_ListTask.end();)
	{
		if ((*it)->IsStopped())
		{
			m_TaskID.Delete((*it)->GetTaskID());
			it = m_ListTask.erase(it);
		}
		else
		{
			(*it)->Update();
			++it;
		}
	}
}


