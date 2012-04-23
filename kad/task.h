#ifndef __KAD_TASK_H__
#define __KAD_TASK_H__
#include "linux_header.h"
class CKad;
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

protected:
	time_t m_Timeout;//seccond
	time_t m_Start;
	short m_TaskID;
	bool m_IsStopped;
	CKad* m_Kad;
};

#endif
