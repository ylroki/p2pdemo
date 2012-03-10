#include "download_file.h"
#include "source.h"

CDownloadFile::CDownloadFile()
{
	m_Status = DS_WAIT; 
	m_Thread = THREAD_ERROR;
}

CDownloadFile::~CDownloadFile()
{}

KDownStatus CDownloadFile::GetStatus()
{
	return m_Status;
}

bool CDownloadFile::Start()
{
	if (m_Status == DS_RUNNING)
		return true;
	m_Status = DS_RUNNING;
	if (0 == pthread_create(&m_Thread, NULL, ThreadFunc, this))
		return true;		
	m_Status = DS_ERROR;
	return false;
}

void CDownloadFile::Stop()
{
	m_Status = DS_DONE;
	pthread_join(m_Thread, NULL);
}

void* CDownloadFile::ThreadFunc(void* arg)
{
	CDownloadFile* down = static_cast<CDownloadFile*>(arg);
	down->Work();
	return ((void*)0);
}

void CDownloadFile::Work()
{
	CSourceManager manager;
	if (RequestSources())
	{
		printf("Download thread work\n");
		manager.Start();
		while (m_Status == DS_RUNNING)	
		{
			Sleep(100);
		}
		manager.Stop();
		printf("Download thread stop\n");
	}
}

bool CDownloadFile::RequestSources()
{
	// TODO: communicate with server, ask for sources


	return true;
}
