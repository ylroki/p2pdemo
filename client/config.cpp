#include "config.h"

CConfig::CConfig()
	:m_LocalIP(),
	m_LocalPort(0),
	m_PeerIP(),
	m_PeerPort(0),
	m_MinPort(9000),
	m_MaxPort(9100),
	m_UpdatePeriod(30)
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

	if (fgets(buf, BUF_SIZE, file) == NULL)
		return false;
	m_UpdatePeriod = atoi(buf);

	if (fgets(buf, BUF_SIZE, file) == NULL)
		return false;
	m_Directory = buf;

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

int CConfig::GetMinPort()
{
	return m_MinPort;
}

int CConfig::GetMaxPort()
{
	return m_MaxPort;
}

int CConfig::GetUpdatePeriod()
{
	return m_UpdatePeriod;
}

std::string CConfig::GetDirectory()
{
	return m_Directory;
}
