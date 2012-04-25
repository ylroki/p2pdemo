#include "task_manager.h"
#include "task.h"
#include "route_table.h"

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

void CTaskManager::Process(short taskID, void* arg)
{
	CAutoLock autolock(&m_Lock);
	std::list<CTask*>::iterator it;
	for (it = m_ListTask.begin(); it != m_ListTask.end(); ++it)
		if ((*it)->GetTaskID() == taskID)
		{
			(*it)->Process(arg);
			break;
		}
}
