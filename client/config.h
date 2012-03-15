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
	int GetLocalPort();
	int GetPeerPort();
	int GetMinPort();
	int GetMaxPort();
	int GetUpdatePeriod();
	std::string GetDirectory();
	std::string GetCacheDir();

private:
	std::string m_LocalIP;
	int m_LocalPort;
	std::string m_PeerIP;
	int m_PeerPort;
	int m_MinPort;
	int m_MaxPort;
	int m_UpdatePeriod;
	std::string m_Directory;
	std::string m_CacheDir;
};

#endif
