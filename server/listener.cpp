#include "linux_header.h"
#include "listener.h"

CListener::CListener()
{
	m_IsStopped = true;
	m_Thread = -1;
}

CListener::~CListener()
{
	assert(m_IsStopped == true);
}

bool CListener::Start()
{
	m_IsStopped = false;
	if (0 == pthread_create(&m_Thread, NULL, ThreadFunc, this))
		return true;
	m_IsStopped = true;
	return false;
}


void CListener::Stop()
{
	m_IsStopped = true;
	pthread_join(m_Thread, NULL);
}

void* CListener::ThreadFunc(void* arg)
{
	CListener* ltner = static_cast<CListener*>(arg);
	ltner->ListenThread();
	return ((void*)0);
}

void CListener::ListenThread()
{
	while (!m_IsStopped)
	{
		// TODO: listen requst from client
		printf("listening...\n");
		sleep(1);
	}
}
