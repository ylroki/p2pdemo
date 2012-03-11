#ifndef __CLIENT_UPLOAD_FILE_H__
#define __CLIENT_UPLOAD_FILE_H__
#include "linux_header.h"
#include "socket_header.h"
#include "config.h"

class CUploadFile
{
public:
	CUploadFile();
	~CUploadFile();
	bool Start(CConfig* config);
	void Stop();

private:
	static void* ThreadFunc(void* arg);
	void Work();
	bool InitSocket();
	void Recv();

	pthread_t m_Thread;
	bool m_Stopped;
	int m_Socket;
	CConfig* m_Config;
};

#endif
