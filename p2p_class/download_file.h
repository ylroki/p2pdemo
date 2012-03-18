#ifndef __CLIENT_DOWNLOAD_FILE_H__
#define __CLIENT_DOWNLOAD_FILE_H__
#include "linux_header.h"
#include "socket_header.h"
#include "config.h"

enum KDownStatus
{
	DS_WAIT,
	DS_RUNNING,
	DS_DONE,
	DS_ERROR
};

struct TPeer
{
	std::string IPv4;
	int port;
};

class CDownloadFile
{
public:
	CDownloadFile();
	~CDownloadFile();
	KDownStatus GetStatus();
	bool Start(CConfig*);
	void Stop();
	

private:
	static void* ThreadFunc(void* arg);
	void Work();
	void RequestSources();
	void UpdateSources();
	bool InitSocket();
	void SelectSocket();
	void RecvMessage();

	KDownStatus m_Status;
	pthread_t m_Thread;
	int m_Socket;
	std::vector<TPeer*> m_VecSource;
	CConfig* m_Config;
};

#endif
