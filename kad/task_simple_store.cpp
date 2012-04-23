#include "task_simple_store.h"
#include "task.h"
#include "kad.h"
CTaskSimpleStore::CTaskSimpleStore(CKad* kad, std::string md5, unsigned long ip, unsigned short port)
	:CTask(kad),
	m_IPv4(ip),
	m_Port(port)
{
	m_Key = CUInt128::FromMD5(md5.c_str());
}

CTaskSimpleStore::~CTaskSimpleStore()
{}

void CTaskSimpleStore::Update()
{
	//TODO
	printf("simple store\n");
}

void CTaskSimpleStore::Process(void* arg)
{
	//TODO
}


