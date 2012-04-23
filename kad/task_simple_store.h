#ifndef __KAD_TASK_SIMPLE_STORE_H__
#define __KAD_TASK_SIMPLE_STORE_H__
#include "task.h"
class CKad;
#include "uint128.h"
class CTaskSimpleStore: public CTask
{
public:
	CTaskSimpleStore(CKad* kad, std::string md5, unsigned long ip, unsigned short port);
	virtual ~CTaskSimpleStore();
	virtual void Update();
	virtual void Process(void* arg);
private:
	CUInt128 m_Key;
	unsigned long m_IPv4;
	unsigned short m_Port;
};


#endif
