#ifndef __CLIENT_SOURCE_H__
#define __CLIENT_SOURCE_H__
#include "socket_header.h"
#include "linux_header.h"

#define MIN_LIS_PORT 9000
#define MAX_LIS_PORT 9050

class CSource
{
public:
	CSource(std::string ip, int port);
	~CSource();
	int InitSocket();
	int GetSocket();
	void Recv();
	void Send();

private:
	std::string m_IPv4;
	int m_Port;
	int m_Socket;
};

class CSourceManager
{
public:
	CSourceManager();
	~CSourceManager();
	bool Start();
	void Stop();


private:
	static void* ThreadFunc(void* arg);
	void Work();
	bool m_Stopped;
	std::vector<CSource> m_VecSource;
	pthread_t m_Thread;
};

#endif
