#include "task_find_value.h"
#include "task.h"
#include "kad.h"

CTaskFindValue::CTaskFindValue(CKad* kad, CUInt128 key)
	:CTask(kad),
	m_Key(key)
{}

CTaskFindValue::~CTaskFindValue()
{}

void CTaskFindValue::Update()
{
	//TODO
	printf("find value\n");
}

void CTaskFindValue::Process(void* arg)
{
	//TODO
}
