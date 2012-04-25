#ifndef __KAD_TASK_FIND_NODE_H__
#define __KAD_TASK_FIND_NODE_H__
#include "uint128.h"
#include "task.h"
class CKad;
struct TNode;
enum KRemoteNodeStatus
{
	RNS_PENDING,
	RNS_TRYING,
	RNS_OK,
	RNS_TIMEOUT
};

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

	CUInt128 m_NodeID;
	KFindNodeStatus m_Status;
	//first is distance
	std::map<CUInt128, TNode> m_Possible;
	std::map<CUInt128, KRemoteNodeStatus> m_PossibleStatus;
	std::map<CUInt128, time_t> m_Trying;
};

#endif
