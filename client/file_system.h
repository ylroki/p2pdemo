#ifndef __CLIENT_FILE_SYSTEM_H__
#define __CLIENT_FILE_SYSTEM_H__
#include "linux_header.h"
#include "socket_header.h"
#include "config.h"

class CFileSystem
{
public:
	CFileSystem();
	~CFileSystem();
	void Start(CConfig*);
	void Stop();

private:
	static void* ThreadFunc(void* arg);
	void Work();
	void FindResources();

	pthread_t m_Thread;
	bool m_Stopped;
	CConfig* m_Config;
	unsigned int m_PastTime;
};

#endif
