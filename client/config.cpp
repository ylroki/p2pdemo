#include "config.h"

CConfig::CConfig()
	:m_LocalIP(),
	m_LocalPort(0),
	m_PeerIP(),
	m_PeerPort(0)
{
}

CConfig::~CConfig()
{
}

bool CConfig::Init(const char* filename)
{
	FILE* file = fopen(filename, "r");
	if (file == NULL)
		return false;

	char buf[BUF_SIZE];
	if (fgets(buf, BUF_SIZE, file) == NULL)
		return false;
	m_LocalIP = buf;
	m_LocalIP = TrimString(m_LocalIP);
	
	if (fgets(buf, BUF_SIZE, file) == NULL)
		return false;
	m_LocalPort = atoi(buf);
	
	if (fgets(buf, BUF_SIZE, file) == NULL)
		return false;
	m_PeerIP = buf;
	m_PeerIP = TrimString(m_PeerIP);
	
	if (fgets(buf, BUF_SIZE, file) == NULL)
		return false;
	m_PeerPort = atoi(buf);

	fclose(file);
	return true;
}

std::string CConfig::GetLocalIP()
{
	return m_LocalIP;
}

std::string CConfig::GetPeerIP()
{
	return m_PeerIP;
}

int CConfig::GetLocalPort()
{
	return m_LocalPort;
}

int CConfig::GetPeerPort()
{
	return m_PeerPort;
}

