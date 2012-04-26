#ifndef __KAD_LOOKUP_H__
#define __KAD_LOOKUP_H__
#include "uint128.h"
#include "linux_header.h"
class CKad;
struct TNode;
class CTask;
enum KRemoteNodeStatus
{
	RNS_PENDING,
	RNS_TRYING,
	RNS_OK,
	RNS_TIMEOUT
};
class CLookup
{
public:
	CLookup(CKad* kad, CUInt128 target, CTask* task);
	~CLookup();
	void Init();
	void SendMessage(CUInt128 distance);
	void ProcessNodes(std::list<TNode>* nodes);
	bool CheckStatus();

private:
	CKad* m_Kad;
	CUInt128 m_Target;
	CTask* m_Task;
	//first is distance
	std::map<CUInt128, TNode> m_Possible;
	std::map<CUInt128, KRemoteNodeStatus> m_PossibleStatus;
	std::map<CUInt128, time_t> m_Trying;
};

#endif
