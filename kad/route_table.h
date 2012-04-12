#ifndef __KAD_ROUTE_TABLE_H__
#define __KAD_ROUTE_TABLE_H__
#include "linux_header.h"
#include "uint128.h"
#include "kad.h"

const int g_LimitK = 4;

struct TNode
{
	std::string IPv4;
	unsigned short Port;
	CUInt128 NodeID;
};

class CRouteTable
{
public:
	CRouteTable();
	~CRouteTable();
	void SetClientID(CUInt128 id);
	void InitTable(const char* filename);
	void GetCloseTo(CUInt128 id, std::list<TNode>* closeNode);
	void TryToInsert(TNode* newNode, void* arg);
	void Insert(TNode* newNode);
	void Print();

private:
	std::list<TNode> m_Bucket[128];
	CUInt128 m_ClientID;
};

#endif
