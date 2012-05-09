#include "task.h"
CTask::CTask(CKad* kad)
	:m_Timeout(600),//10 min
	m_TaskID(-1),
	m_IsStopped(false),
	m_Kad(kad),
	m_CallbackFunc(NULL),
	m_Caller(NULL),
	m_CallbackArg(NULL),
	m_Start(0)
{}

CTask::~CTask()
{}

void CTask::SetTimeout(time_t sec)
{
	m_Timeout = sec;
}

void CTask::SetTaskID(short id)
{
	m_TaskID = id;
	m_Start = GetNowSeconds();
}

bool CTask::IsTimeout()
{
	if (m_Start == 0)
		return false;
	time_t now = GetNowSeconds();
	if (now - m_Start >= m_Timeout)
		return true;
	return false;
}

short CTask::GetTaskID()
{
	return m_TaskID;
}

bool CTask::IsStopped()
{
	return m_IsStopped;
}

void CTask::SetCallback(TaskCallback func, void* caller, void* arg)
{
	m_CallbackFunc = func;
	m_Caller = caller;
	m_CallbackArg = arg;
}
