#ifndef __KAD_TASK_H__
#define __KAD_TASK_H__
#include "linux_header.h"
class CKad;
typedef void (*TaskCallback)(void* caller, void* arg);
class CTask
{
public:
	CTask(CKad* kad);
	virtual ~CTask();
	virtual void Update() = 0;
	virtual void Process(void* arg) = 0;
	void SetTimeout(time_t millisec);
	void SetTaskID(short id);
	short GetTaskID();
	bool IsStopped();
	void SetCallback(TaskCallback func, void* caller, void* arg);

protected:
	time_t m_Timeout;//seccond
	time_t m_Start;
	short m_TaskID;
	bool m_IsStopped;
	CKad* m_Kad;
	TaskCallback m_CallbackFunc;
	void* m_Caller;
	void* m_CallbackArg;
};

#endif
