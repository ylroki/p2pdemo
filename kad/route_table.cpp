#include "route_table.h"

CRouteTable::CRouteTable()
	:m_ClientID()
{
	for (size_t i = 0; i < 128; ++i)
		m_Bucket[i].clear();
}

CRouteTable::~CRouteTable()
{}

void CRouteTable::TryToInsert(TNode* newNode, void* arg)
{
	CUInt128 distance = newNode->NodeID.XOR(m_ClientID);
	size_t index = distance.FirstOneBit();
	std::list<TNode>::iterator it;
	for (it = m_Bucket[index].begin(); it != m_Bucket[index].end(); ++it)
	{
		if ((it->NodeID).EqualTo(newNode->NodeID))
		{
			// Maybe the ip or port of this nodeID is changed.
			*it = *newNode;
			break;
		}
	}
	if (it != m_Bucket[index].end())
	{
		// That means newNode is already is in the bucket.
		// Just remove it to the tail
		printf("new node already exist\n");
		TNode tmp = *it;
		m_Bucket[index].erase(it);
		m_Bucket[index].push_back(tmp);
	}
	else
	{
		if (m_Bucket[index].size() >= g_LimitK)
		{
			// bucket is full.
			printf("bucket is full\n");
			bool exist = false;
			std::list<TNode>::iterator itBegin = m_Bucket[index].begin();
			if (arg)
			{
				CKad* kad = static_cast<CKad*>(arg);
				exist = kad->Ping(*itBegin);
			}
			if (exist)
			{
				// the least-recently seen node reponse.
				// Remove it to the tail.
				TNode tmp = *itBegin;
				m_Bucket[index].pop_front();
				m_Bucket[index].push_back(tmp);
			}
			else
			{
				m_Bucket[index].pop_front();
				m_Bucket[index].push_back(*newNode);
			}
		}
		else
		{
			printf("insert new node\n");
			m_Bucket[index].push_back(*newNode);
		}
	}
}

void CRouteTable::GetCloseTo(CUInt128 id, std::list<TNode>* closeNode)
{
	//TODO

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
			TNode node;
			node.IPv4 = buf;
			node.Port = port;
			node.NodeID = CUInt128::FromMD5(md5);
			Insert(&node);
		}
	}
}

void CRouteTable::Insert(TNode* newNode)
{
	CUInt128 distance = newNode->NodeID.XOR(m_ClientID);
	size_t index = distance.FirstOneBit();
	m_Bucket[index].push_back(*newNode);
}

void CRouteTable::SetClientID(CUInt128 id)
{
	m_ClientID = id;
}

void CRouteTable::Print()
{
	for (int i = 0; i < 128; ++i)
	{
		if (!m_Bucket[i].empty())
		{
			printf("Index %d:\n", i);
			std::list<TNode>::iterator it;
			for (it = m_Bucket[i].begin(); it != m_Bucket[i].end(); ++it)
			{
				it->NodeID.Print();
			}
		}
	}
}
