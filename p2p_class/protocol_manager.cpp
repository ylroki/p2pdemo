#include "protocol_manager.h"

CProtocolManager::CProtocolManager(CConfig* config)
	:m_Config(config)
{}

CProtocolManager::~CProtocolManager()
{}

void CProtocolManager::AddHash(unsigned char* hexHash)
{
	vecHashes.insert(vecHashes.end(), hexHash, hexHash+16);		
}

const int g_NHashes = 50;
void CProtocolManager::SendCommand(char id, int sock, ...)
{
	if (sock == SOCKET_ERROR)
		sock = socket(AF_INET, SOCK_DGRAM, 0);
	switch (id)
	{
	case 0x01:
		{
			char buf[BUF_SIZE];
			for (size_t i = 0 ; i < vecHashes.size(); i+=g_NHashes)
			{
				int n = Min(g_NHashes, vecHashes.size() - i);
				int len = GenerateCommand(buf, 0x01, m_Config->GetPeerPort(), n, &(vecHashes[i]));
				SendTo(sock, buf, m_Config->GetServerIP().c_str(), m_Config->GetServerPort());
			}
		}

	}
}
