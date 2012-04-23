#include "kad_protocol.h"
#include "kad.h"
#include "task_manager.h"

CKadProtocol::CKadProtocol(CKad* kad)
	:m_Kad(kad)
{}

CKadProtocol::~CKadProtocol()
{}

void CKadProtocol::RecvMessage(int sockfd)
{
	if (sockfd == SOCKET_ERROR)	
		return ;
	char abuf[MAX_ADDR_SIZE];
	socklen_t alen = MAX_ADDR_SIZE;
	char buf[BUF_SIZE];
	memset(buf, 0, sizeof(buf));
	int n = recvfrom(sockfd, buf, BUF_SIZE, 0, (struct sockaddr*)abuf, &alen);
	if (n > 0)
	{
		// In each package, first two object is cmd, remoteID.
		CMemoryStream reader(buf, n, BUF_SIZE);
		char cmd = reader.ReadInteger<char>();
		unsigned char remoteHex[16];
		reader.ReadBuffer(remoteHex, 16);
		CUInt128 remoteID = CUInt128::FromHex(remoteHex);
		unsigned long remoteIP = ntohl(((struct sockaddr_in*)abuf)->sin_addr.s_addr);
		unsigned short remotePort = ntohs(((struct sockaddr_in*)abuf)->sin_port);
		m_Kad->AddNode(remoteID, remoteIP, remotePort); //Add remote infomation in route table.

		// Get self ID.
		unsigned char selfID[16];
		m_Kad->GetClientIDHex(selfID);
		switch (cmd)
		{
		case 0x40://ping request
			{
				short taskID = ntohs(reader.ReadInteger<short>());
				char sendBuf[BUF_SIZE];
				CMemoryStream sender(sendBuf, 0, BUF_SIZE);
				sender.WriteInteger<char>(0x41);
				sender.WriteBuffer(selfID, 16);
				sender.WriteInteger<short>(htons(taskID));
				sendto(sockfd, sendBuf, sender.GetSize(), 0, (struct sockaddr*)abuf, alen);
				break;
			}
		case 0x41:// ping response
			{
				short taskID = ntohs(reader.ReadInteger<short>());
				m_Kad->GetTaskManager()->ProcessPingResponse(taskID);
				break;
			}
		default:
			{
				break;
			}
		}
	}
}
