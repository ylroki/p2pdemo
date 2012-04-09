#include "kad.h"

CKad::CKad(CConfig* config)
	:m_Config(config),
	m_Stopped(true),
	m_WorkThread(THREAD_ERROR),
	m_ListenThread(THREAD_ERROR)
{}

CKad::~CKad()
{}

bool CKad::Start()
{
	if (!m_Stopped)
		return true;
	m_Stopped = false;
	if (0 == pthread_create(&m_WorkThread, NULL, WorkThread, this))
		return true;
	m_Stopped = true;
	return false;
}

void CKad::Stop()
{
	m_Stopped = true;
	if (m_WorkThread != THREAD_ERROR)
		pthread_join(m_WorkThread, NULL);
}

void* CKad::WorkThread(void* arg)
{
	CKad* kad = static_cast<CKad*>(arg);
	kad->Work();
	return ((void*)0);
}

void CKad::Work()
{
	if (pthread_create(&m_ListenThread, NULL, ListenThread, this))
		return;
	JoinKad();
	while (!m_Stopped)
	{
		// TODO
		printf("work thread\n");
	}
	if (m_ListenThread != THREAD_ERROR)
		pthread_join(m_ListenThread, NULL);
	printf("stop working\n");
}

void* CKad::ListenThread(void* arg)
{
	CKad* kad = static_cast<CKad*>(arg);
	kad->Listen();
	return ((void*)0);
}

void CKad::Listen()
{
	while (!m_Stopped)
	{
		// TODO
		printf("listen thread\n");
		Sleep(1);
	}
	printf("stop listening\n");
}

void CKad::JoinKad()
{}
