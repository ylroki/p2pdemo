#include "route_table.h"

CRouteTable::CRouteTable(CRouteTable* parent, CUInt128 id, short depth, bool has)
	:m_Parent(NULL),
	m_Depth(depth),
	m_ClientID(id),
	m_IsLeaf(true),
	m_HasClient(has)
{
	m_Child[0] = m_Child[1] = NULL;
	m_Bucket.clear();
}

CRouteTable::~CRouteTable()
{
	if (m_Child[0])
		delete m_Child[0];
	if (m_Child[1])
		delete m_Child[1];
	if (m_IsLeaf)
	{
		std::list<TNode*>::iterator it;
		for (it = m_Bucket.begin(); it != m_Bucket.end(); ++it)
			delete *it;
	}
}


void CRouteTable::GetCloseTo(CUInt128 id, std::list<TNode>* closeNode, int number)
{
	if (m_IsLeaf)
	{
		// leaf.
		std::list<TNode*>::iterator it = m_Bucket.begin();
		while (number-- && it != m_Bucket.end())
		{
			closeNode->push_back(*(*it));
			++it;
		}
	}
	else
	{
		int index = id.GetBit(127 - m_Depth);
		m_Child[index]->GetCloseTo(id, closeNode, number);
		if (closeNode->size() < number)
		{
			index = (index + 1) % 2;
			m_Child[index]->GetCloseTo(id, closeNode, number - closeNode->size());
		}
	}
}

void CRouteTable::InitTable(const char* filename)
{
	FILE* file = fopen(filename, "r");
	if (file)
	{
		char buf[BUF_SIZE];
		unsigned short port;
		char md5[33];
		while (fscanf(file, "%s %hu %s", buf, &port, md5) != EOF)
		{
			TNode* node = new TNode;
			node->IPv4 = buf;
			node->Port = port;
			node->NodeID = CUInt128::FromMD5(md5);
			Insert(node);
		}
	}
}

void CRouteTable::Insert(TNode* newNode)
{
	if (!m_IsLeaf)
	{
		// Not leaf, insert in child routetable.
		m_Child[newNode->NodeID.GetBit(127 - m_Depth)]->Insert(newNode);
	}
	else
	{
		std::list<TNode*>::iterator it;
		for (it = m_Bucket.begin(); it != m_Bucket.end(); ++it)
			if ((*it)->NodeID.EqualTo(newNode->NodeID))
				return ;
		if (m_Bucket.size() < KAD_LIMIT_K)
		{
			// Bucket is not full.
			m_Bucket.push_back(newNode);
		}
		else
		{
			if (TryToSplit() == true)
				Insert(newNode);
		}
	}
}

void CRouteTable::Print()
{
	if (m_IsLeaf)
	{
		printf("leaf depth %hd\n", m_Depth);
		std::list<TNode*>::iterator it;
		for (it = m_Bucket.begin(); it != m_Bucket.end(); ++it)
			(*it)->NodeID.Print();
	}
	else
	{
		printf("inner depth %hd\n", m_Depth);
		m_Child[0]->Print();
		m_Child[1]->Print();
	}
}

bool CRouteTable::TryToSplit()
{
	if (m_Depth <= KAD_LIMIT_SPLIT_D || m_HasClient)
	{
		m_Child[0] = new CRouteTable(this, m_ClientID, m_Depth + 1, 
			m_HasClient&&(m_ClientID.GetBit(127 - m_Depth) == 0));
		m_Child[1] = new CRouteTable(this, m_ClientID, m_Depth + 1, 
			m_HasClient&&(m_ClientID.GetBit(127 - m_Depth) == 1));
		m_IsLeaf = false;
		std::list<TNode*>::iterator it;
		for (it = m_Bucket.begin(); it != m_Bucket.end(); ++it)
			m_Child[(*it)->NodeID.GetBit(127 - m_Depth)]->Insert(*it);
		m_Bucket.clear();
		return true;
	}
	return false;
}
