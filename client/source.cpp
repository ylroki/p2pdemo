#include "source.h"

CSource::CSource(std::string ip, int port)
	:m_IPv4(ip),
	m_Port(port),
	m_Socket(SOCKET_ERROR)
{
}

CSource::~CSource()
{
	if (m_Socket != SOCKET_ERROR)
	{
		close(m_Socket);
		m_Socket = SOCKET_ERROR;
	}
}

int CSource::InitSocket()
{
	m_Socket = socket(AF_INET, SOCK_DGRAM, 0);
	for (int i = MIN_LIS_PORT; i <= MAX_LIS_PORT; ++i)
		if (Bind(m_Socket, NULL, i) == true)
			return m_Socket;
	close(m_Socket);
	m_Socket = SOCKET_ERROR;
	return m_Socket;
}

int CSource::GetSocket()
{
	return m_Socket;
}

void CSource::Recv()
{
	char buf[BUF_SIZE];
	memset(buf, 0, sizeof(buf));
	recv(m_Socket, buf, BUF_SIZE, 0);
	DebugLog(buf);
}

void CSource::Send()
{
	SendTo(m_Socket, "hello", m_IPv4.c_str(), m_Port);	
}

CSourceManager::CSourceManager()
	:m_Stopped(true),
	m_Thread(THREAD_ERROR)
{
	m_VecSource.clear();
}

CSourceManager::~CSourceManager()
{}

bool CSourceManager::Start()
{
	m_Stopped = false;
	if (0 == pthread_create(&m_Thread, NULL, ThreadFunc, this))
		return true;
	m_Stopped = true;
	return false;
}

void CSourceManager::Stop()
{
	m_Stopped = true;
	pthread_join(m_Thread, NULL);
}

void* CSourceManager::ThreadFunc(void* arg)
{
	CSourceManager* manager = static_cast<CSourceManager*>(arg);
	manager->Work();
	return ((void*)0);
}

void CSourceManager::Work()
{
	m_VecSource.push_back(CSource("127.0.0.1", 31415));
	//debug
	fd_set lisSet;
	FD_ZERO(&lisSet);
	int maxFd = -1;
	for (size_t i = 0; i < m_VecSource.size(); ++i)
	{
		int sock = m_VecSource[i].InitSocket();
		if (sock != SOCKET_ERROR)
		{
			maxFd = sock > maxFd ? sock : maxFd;
			FD_SET(sock, &lisSet);
		}
	}
	while (!m_Stopped)
	{
		timeval t;
		t.tv_sec = 0;
		t.tv_usec = 100;
		fd_set tmpSet = lisSet;
		int n = select(maxFd + 1, &tmpSet, NULL, NULL, &t);
		for (size_t i = 0; i < m_VecSource.size(); ++i)
		{
			if (FD_ISSET(m_VecSource[i].GetSocket(), &tmpSet))
				m_VecSource[i].Recv();
		}
		sleep(1);
	}
}

