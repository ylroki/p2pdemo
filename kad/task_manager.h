#ifndef __KAD_TASK_MANAGER_H__
#define __KAD_TASK_MANAGER_H__
#include "linux_header.h"
#include "route_table.h"
class CTask
{
public:
	CTask();
	virtual ~CTask();
	virtual void Update() = 0;
	void SetTimeout(time_t microsec);
private:
	time_t m_Timeout;
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

class CTaskManager
{
public:
	CTaskManager();
	~CTaskManager();
	void Add(CTask* task);
	void Update();

private:
	std::vector<CTask*> m_VecTask;
};


#endif
