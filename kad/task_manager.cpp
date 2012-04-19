#include "task_manager.h"
CTask::CTask()
	:m_Timeout(600000)//10 min
{}

CTask::~CTask()
{}

void CTask::SetTimeout(time_t microsec)
{
	m_Timeout = microsec;
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


CTaskManager::CTaskManager()
{
	m_VecTask.clear();
}

CTaskManager::~CTaskManager()
{
	for (size_t i = 0; i < m_VecTask.size(); ++i)
		delete m_VecTask[i];
}

void CTaskManager::Add(CTask* task)
{
	printf("Add\n");
	m_VecTask.push_back(task);
}

void CTaskManager::Update()
{
	printf("manager update\n");
	printf("size: %d\n", m_VecTask.size());
	for (size_t i = 0; i < m_VecTask.size(); ++i)
		m_VecTask[i]->Update();
}


