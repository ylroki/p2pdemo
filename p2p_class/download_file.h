#ifndef __CLIENT_DOWNLOAD_FILE_H__
#define __CLIENT_DOWNLOAD_FILE_H__
#include "linux_header.h"
#include "socket_header.h"
#include "config.h"
#include "stream.h"
#include "md5_header.h"
#include "command.h"
#include "protocol_manager.h"

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
	CDownloadFile(const char* md5);
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

	std::string m_MD5;
	KDownStatus m_Status;
	pthread_t m_Thread;
	int m_Socket;
	std::vector<TPeer> m_VecSource;
	std::vector<TPeer> m_VecWorkSource;
	CConfig* m_Config;
	CProtocolManager* m_Protocol;
};

#endif
