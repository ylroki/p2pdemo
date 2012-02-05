#include <download_file.h>

CDownloadFile::CDownloadFile()
{
	m_Status = DS_WAIT; 
	m_Thread = -1;
	m_VecSource.clear();
}

CDownloadFile::~CDownloadFile()
{}

CDownloadFile::GetStatus()
{
	return m_Status;
}

bool CDownloadFile::Start()
{
	m_Status = DS_RUNNIG;
	if (0 == pthread_create(&m_Thread, NULL, ThreadFunc, this))
		return true;		
	m_Status = DS_ERROR;
	return false
}

void CDownloadFile::Stop()
{
	m_Status = DS_DONE;
	pthread_join(m_Thread, NULL);
}

void* CDownloadFile::ThreadFunc(void* arg)
{
	CDownloadFile down = static_cast<CDownloadFile*(arg);
	down.Work();
	return ((void*)0);
}

void CDownloadFile::Work()
{
	if (RequestSources())
	{
		while (m_Status == DS_RUNNIG)	
		{
			// TODO: download a file, manage sources
			for (size_t i = 0; i < m_VecSource.size(); ++i)
			{
				// TODO: update each source 
			}
			sleep(1);
		}
	}
}

bool CDownloadFile::RequestSources()
{
	// TODO: communicate with server, ask for sources

	return true;
}
