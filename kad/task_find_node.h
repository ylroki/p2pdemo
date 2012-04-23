#ifndef __KAD_TASK_FIND_NODE_H__
#define __KAD_TASK_FIND_NODE_H__
#include "uint128.h"
#include "task.h"
class CKad;
class CTaskFindNode: public CTask
{
public:
	CTaskFindNode(CKad* kad, CUInt128 id);
	virtual ~CTaskFindNode();
	virtual void Update();
	virtual void Process(void* arg);
private:
	CUInt128 m_NodeID;
};

#endif
