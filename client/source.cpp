#include "souce.h"

CSource::CSource(std::string ip, int port)
	:m_IPv4(ip),
	m_Port(port)
{
}

CSource::~CSource()
{}

void CSource::RequestBlock()
{}

bool CSource::Start()
{
	m_Stopped = false;
	if (0 == pthread_create(&m_Thread, NULL, ThreadFunc, this))
		return true;
	m_Stopped = true;
	return false;
}

void CSource::Stop()
{
	m_Stopped = true;
	pthread_join(m_Thread, NULL);
}

void* CSource::ThreadFunc(void* arg)
{
	CSource* source = static_cast<CSource*>(arg);
	source->Work();
	return ((void*)0);
}

void CSource::Work()
{
	// TODO: listening
}

