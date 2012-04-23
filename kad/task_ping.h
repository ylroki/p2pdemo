#ifndef __KAD_TASK_PING_H__
#define __KAD_TASK_PING_H__
#include "task.h"
class CKad;
class TNode;
enum KPingStatus
{
	PS_INIT,
	PS_WAIT,
	PS_END
};
class CTaskPing: public CTask
{
public:
	CTaskPing(CKad* kad, TNode& node);
	virtual ~CTaskPing();
	virtual void Update();
	virtual void Process(void* arg);
private:
	TNode* m_Node;
	KPingStatus m_Status;
};


#endif
