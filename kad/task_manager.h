#ifndef __KAD_TASK_MANAGER_H__
#define __KAD_TASK_MANAGER_H__
#include "linux_header.h"
#include "route_table.h"
#include "id_helper.h"
#include "auto_lock.h"
class CTask
{
public:
	CTask();
	virtual ~CTask();
	virtual void Update() = 0;
	void SetTimeout(time_t millisec);
	void SetTaskID(short id);
	short GetTaskID();
	bool IsStopped();

private:
	time_t m_Timeout;
	short m_TaskID;
	bool m_IsStopped;
};

class CTaskSimpleStore: public CTask
{
public:
	CTaskSimpleStore(std::string md5, unsigned long ip, unsigned short port);
	virtual ~CTaskSimpleStore();
	virtual void Update();
private:
	CUInt128 m_Key;
	unsigned long m_IPv4;
	unsigned short m_Port;
};

class CTaskPing: public CTask
{
public:
	CTaskPing(TNode& node);
	virtual ~CTaskPing();
	virtual void Update();
private:
	TNode* m_Node;
};

class CTaskFindNode: public CTask
{
public:
	CTaskFindNode(CUInt128 id);
	virtual ~CTaskFindNode();
	virtual void Update();
private:
	CUInt128 m_NodeID;
};

class CTaskFindValue: public CTask
{
public:
	CTaskFindValue(CUInt128 key);
	virtual ~CTaskFindValue();
	virtual void Update();
private:
	CUInt128 m_Key;
};

class CTaskManager
{
public:
	CTaskManager();
	~CTaskManager();
	void Add(CTask* task);
	void Update();

private:
	std::list<CTask*> m_ListTask;
	std::list<CTask*> m_ListPending;
	CLock m_Lock;
	CIDHelper m_TaskID;
};


#endif
