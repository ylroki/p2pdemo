#include "protocol.h"

void DealMessage(const char* recvBuf, const int rLen, 
	const int sockfd, const struct sockaddr* addr, const int alen)
{
	KProtocol pro = recvBuf[0];
	switch (pro)
	{
	case P_GET_FILE_DATA:
		{
			char buf[BUF_SIZE * 2];
		}
	default:
		{
			printf("error protocol\n");
		}
	}
}
