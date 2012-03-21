#include "config.h"

CConfig::CConfig()
	:m_LocalIP(),
	m_LocalPort(0),
	m_PeerIP(),
	m_PeerPort(0),
	m_MinPort(9000),
	m_MaxPort(9100),
	m_UpdatePeriod(30),
	m_ServerIP(),
	m_ServerPort(0)
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
	m_Directory = TrimString(m_Directory);

	if (fgets(buf, BUF_SIZE, file) == NULL)
		return false;
	m_CacheDir = buf;
	m_CacheDir = TrimString(m_CacheDir);

	if (fgets(buf, BUF_SIZE, file) == NULL)
		return false;
	m_ServerIP = buf;
	m_ServerIP = TrimString(m_ServerIP);
	
	if (fgets(buf, BUF_SIZE, file) == NULL)
		return false;
	m_ServerPort = atoi(buf);

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

unsigned short CConfig::GetLocalPort()
{
	return m_LocalPort;
}

unsigned short CConfig::GetPeerPort()
{
	return m_PeerPort;
}

unsigned short CConfig::GetMinPort()
{
	return m_MinPort;
}

unsigned short CConfig::GetMaxPort()
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

std::string CConfig::GetCacheDir()
{
	return m_CacheDir;
}

std::string CConfig::GetServerIP()
{
	return m_ServerIP;
}

unsigned short CConfig::GetServerPort()
{
	return m_ServerPort;
}
