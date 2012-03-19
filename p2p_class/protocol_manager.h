#ifndef __P2P_CLASS_PROTOCOL_MANAGER_H__
#define __P2P_CLASS_PROTOCOL_MANAGER_H__
#include "linux_header.h"
#include "config.h"

class CProtocolManager
{
public:
	CProtocolManager();
	~CProtocolManager();
	void AddHash(unsigned char* md5);
	void SendCommand(char id, ...);

private:
	CConfig* m_Config;
};

#endif
