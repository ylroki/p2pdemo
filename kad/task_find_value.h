#ifndef __KAD_TASK_FIND_VALUE_H__
#define __KAD_TASK_FIND_VALUE_H__
class CKad;
class CLookup;
#include "task.h"
#include "uint128.h"

enum KFindValueStatus
{
	FVS_INIT,
	FVS_UPDATE,
	FVS_END
};
class CTaskFindValue: public CTask
{
public:
	CTaskFindValue(CKad* kad, CUInt128 key);
	virtual ~CTaskFindValue();
	virtual void Update();
	virtual void Process(void* arg);
private:
	CLookup* m_Lookup;
	CUInt128 m_Key;
	KFindValueStatus m_Status;
};


#endif
