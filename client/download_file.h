#ifndef __CLIENT_DOWNLOAD_FILE_H__
#define __CLIENT_DOWNLOAD_FILE_H__
#include "linux_header.h"
enum KDownStatus
{
	DS_WAIT,
	DS_RUNNING,
	DS_DONE,
	DS_ERROR
};
class CDownloadFile
{
public:
	CDownloadFile();
	~CDownloadFile();
	KDownStatus GetStatus();
	bool Start();
	void Stop();
	

private:
	static void* ThreadFunc(void* arg);
	void Work();
	bool RequestSources();
	KDownStatus m_Status;
	pthread_t m_Thread;
};

#endif
