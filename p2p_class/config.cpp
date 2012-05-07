#include "config.h"

CConfig::CConfig()
	:m_LocalIP("127.0.0.1"),
	m_LocalPort(0),
	m_PeerIP("127.0.0.1"),
	m_PeerPort(0),
	m_MinPort(9000),
	m_MaxPort(9100),
	m_UpdatePeriod(30),
	m_ServerIP("127.0.0.1"),
	m_ServerPort(0),
	m_KadPort(0)
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
	while (fgets(buf, BUF_SIZE, file))
	{
		// NAME:VALUE
		std::string equ = buf;
		equ = TrimString(equ);
		size_t pos = equ.find_first_of(':');
		if (pos != equ.size())
		{
			std::string name = equ.substr(0, pos);
			std::string value = equ.substr(pos + 1, equ.size() - pos - 1);
			printf("%s:%s\n", name.c_str(), value.c_str());
			if (name == "local port")
				m_LocalPort = atoi(value.c_str());
			else if (name == "peer port")
				m_PeerPort = atoi(value.c_str());
			else if (name == "update period")
				m_UpdatePeriod = atoi(value.c_str());
			else if (name == "resource dir")
				m_Directory = value;
			else if (name == "cache dir")
				m_CacheDir = value;
			else if (name == "server ip")
				m_ServerIP = value;
			else if (name == "server port")
				m_ServerPort = atoi(value.c_str());
			else if (name == "kad port")
				m_KadPort = atoi(value.c_str());
		}
	}
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

unsigned short CConfig::GetKadPort()
{
	return m_KadPort;
}
