#ifndef __CLIENT_CONFIG_H__
#define __CLIENT_CONFIG_H__
#include "linux_header.h"
#include "string_header.h"

class CConfig
{
public:
	CConfig();
	~CConfig();
	bool Init(const char* filename);
	std::string GetLocalIP();
	std::string GetPeerIP();
	unsigned short GetLocalPort();
	unsigned short GetPeerPort();
	unsigned short GetMinPort();
	unsigned short GetMaxPort();
	int GetUpdatePeriod();
	std::string GetDirectory();
	std::string GetCacheDir();
	std::string GetServerIP();
	unsigned short GetServerPort();

private:
	std::string m_LocalIP;
	int m_LocalPort;
	std::string m_PeerIP;
	unsigned short m_PeerPort;
	unsigned short m_MinPort;
	unsigned short m_MaxPort;
	int m_UpdatePeriod;
	std::string m_Directory;
	std::string m_CacheDir;
	std::string m_ServerIP;
	unsigned short m_ServerPort;
};

#endif
