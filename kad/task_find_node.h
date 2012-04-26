#ifndef __KAD_TASK_FIND_NODE_H__
#define __KAD_TASK_FIND_NODE_H__
#include "uint128.h"
#include "task.h"
class CLookup;
class CKad;
struct TNode;


enum KFindNodeStatus
{
	FNS_INIT,
	FNS_UPDATE,
	FNS_END
};

class CTaskFindNode: public CTask
{
public:
	CTaskFindNode(CKad* kad, CUInt128 id);
	virtual ~CTaskFindNode();
	virtual void Update();
	virtual void Process(void* arg);
private:
	bool CheckStatus();
	void SendMessage(CUInt128 distance);

	CLookup* m_Lookup;
	CUInt128 m_NodeID;
	KFindNodeStatus m_Status;
};

#endif
