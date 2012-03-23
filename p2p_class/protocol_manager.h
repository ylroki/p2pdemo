#ifndef __P2P_CLASS_PROTOCOL_MANAGER_H__
#define __P2P_CLASS_PROTOCOL_MANAGER_H__
#include "linux_header.h"
#include "socket_header.h"
#include "config.h"
#include "command.h"
#include "md5_header.h"
#include "file_system.h"
#include "upload_file.h"
#include "download_file.h"


class CProtocolManager
{
public:
	CProtocolManager(CConfig*);
	~CProtocolManager();
	void AddHash(unsigned char* hexHash);
	void SendCommand(char id, int sock, ...);
	void Response(int sockfd = SOCKET_ERROR, void* arg = NULL);

private:
	CConfig* m_Config;
	std::vector<unsigned char> vecHashes;
};

#endif
