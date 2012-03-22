#ifndef __P2P_CLASS_PROTOCOL_MANAGER_H__
#define __P2P_CLASS_PROTOCOL_MANAGER_H__
#include "linux_header.h"
#include "socket_header.h"
#include "config.h"
#include "command.h"

class CProtocolManager
{
public:
	CProtocolManager(CConfig*);
	~CProtocolManager();
	void AddHash(unsigned char* hexHash);
	void SendCommand(char id, int sock, ...);
	void Response(int sockfd = SOCKET_ERROR, ...); 

private:
	CConfig* m_Config;
	std::vector<unsigned char> vecHashes;
};

#endif
