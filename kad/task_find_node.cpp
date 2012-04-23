#include "task_find_node.h"
#include "kad.h"
CTaskFindNode::CTaskFindNode(CKad* kad, CUInt128 id)
	:CTask(kad),
	m_NodeID(id)
{
}

CTaskFindNode::~CTaskFindNode()
{}

void CTaskFindNode::Update()
{
	//TODO
	printf("find node\n");
}

void CTaskFindNode::Process(void* arg)
{
	//TODO
}
