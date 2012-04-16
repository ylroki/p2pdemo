#ifndef __KAD_ROUTE_TABLE_H__
#define __KAD_ROUTE_TABLE_H__
#include "linux_header.h"
#include "uint128.h"
#include "define.h"

struct TNode
{
	std::string IPv4;
	unsigned short Port;
	CUInt128 NodeID;
};

class CRouteTable
{
public:
	CRouteTable(CRouteTable* parent, CUInt128 id, short depth, bool has);
	~CRouteTable();
	void InitTable(const char* filename);
	// shouldn't return pointer to TNode.
	void GetCloseTo(CUInt128 id, std::list<TNode>* closeNode, int number = KAD_LIMIT_K);
	void Insert(TNode* newNode);
	bool TryToSplit();
	void Print();

private:
	CUInt128 m_ClientID;
	bool m_HasClient;
	short m_Depth;
	CRouteTable* m_Child[2];
	CRouteTable* m_Parent;
	bool m_IsLeaf;
	// I don't know how large bucket will be, so use pointer of node from new operation.
	std::list<TNode*> m_Bucket;
};

#endif
