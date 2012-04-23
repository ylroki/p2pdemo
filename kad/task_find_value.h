#ifndef __KAD_TASK_FIND_VALUE_H__
#define __KAD_TASK_FIND_VALUE_H__
class CKad;
#include "task.h"
#include "uint128.h"
class CTaskFindValue: public CTask
{
public:
	CTaskFindValue(CKad* kad, CUInt128 key);
	virtual ~CTaskFindValue();
	virtual void Update();
	virtual void Process(void* arg);
private:
	CUInt128 m_Key;
};


#endif
