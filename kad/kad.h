#ifndef __KAD_KAD_H__
#define __KAD_KAD_H__
#include "linux_header.h"
#include "socket_header.h"
#include "config.h"

class CKad
{
public:
	CKad(CConfig* config);
	~CKad();
	bool Start();
	void Stop();

private:
	static void* WorkThread(void* arg);
	void Work();
	static void* ListenThread(void* arg);
	void Listen();
	void JoinKad();

	CConfig* m_Config;
	bool m_Stopped;
	pthread_t m_WorkThread;
	pthread_t m_ListenThread;
	
};
#endif
