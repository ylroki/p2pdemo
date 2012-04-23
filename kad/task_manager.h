#ifndef __KAD_TASK_MANAGER_H__
#define __KAD_TASK_MANAGER_H__
#include "linux_header.h"
#include "id_helper.h"
#include "auto_lock.h"
class CTask;

class CTaskManager
{
public:
	CTaskManager();
	~CTaskManager();
	void Add(CTask* task);
	void Update();
	void ProcessPingResponse(short taskID);

private:
	std::list<CTask*> m_ListTask;
	std::list<CTask*> m_ListPending;
	CLock m_Lock;
	CIDHelper m_TaskID;
};


#endif
