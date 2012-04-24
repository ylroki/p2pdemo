#ifndef __KAD_TASK_SIMPLE_STORE_H__
#define __KAD_TASK_SIMPLE_STORE_H__
#include "task.h"
class CKad;
class TNode;
#include "uint128.h"

enum KSimpleStoreStatus
{
	SSS_INIT,
	SSS_UPDATE,
	SSS_END
};

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
	KSimpleStoreStatus m_Status;
	std::list<TNode> m_CloseNode;
};


#endif
