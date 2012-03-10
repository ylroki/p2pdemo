#include "upload_file.h"
#include "source.h"

CUploadFile::CUploadFile()
	:m_Thread(THREAD_ERROR),
	m_Stopped(true),
	m_Socket(SOCKET_ERROR),
	m_Config(NULL)
{
}

CUploadFile::~CUploadFile()
{}


bool CUploadFile::Start(CConfig* config)
{
	if (!m_Stopped)
		return true;
	m_Config = config;
	if (InitSocket() == false)
		return false;
		
	m_Stopped = false;
	if (0 == pthread_create(&m_Thread, NULL, ThreadFunc, this))
		return true;		
	m_Stopped = true;
	return false;
}

void CUploadFile::Stop()
{
	m_Stopped = true;
	if (m_Thread != THREAD_ERROR)
		pthread_join(m_Thread, NULL);
}

void* CUploadFile::ThreadFunc(void* arg)
{
	CUploadFile* up = static_cast<CUploadFile*>(arg);
	up->Work();
	return ((void*)0);
}

void CUploadFile::Work()
{
	if (m_Socket == SOCKET_ERROR)
		return;
	int maxFd = m_Socket + 1;
	struct timeval t;
	t.tv_sec = 0;
	t.tv_usec = 100;
	printf("Upload thread work\n");
	while (!m_Stopped)	
	{
		fd_set rSet;
		FD_ZERO(&rSet);
		FD_SET(m_Socket, &rSet);
		if (select(maxFd, &rSet, NULL, NULL, &t))
		{
			if (FD_ISSET(m_Socket, &rSet))
			{
				//Recv();
			}
		}
		Sleep(100);
	}
	printf("Upload thread stop\n");
}

bool CUploadFile::InitSocket()
{
	if ((m_Socket = socket(AF_INET, SOCK_DGRAM, 0)) == SOCKET_ERROR)
		return false;
	printf("%d\n", m_Socket);
		
	return Bind(m_Socket, NULL, m_Config->GetPeerPort());
}
