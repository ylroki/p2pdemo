#ifndef __CLIENT_PROTOCOL_H__
#define __CLIENT_PROTOCOL_H__

enum KProtocol
{
	P_LOGIN = 1,
	P_LOGOUT = 2,
	P_GET_FILE_DATA = 10,
	/*byte|content
	 *1|protocol
	 *16|hash
	 *4|offset1
	 *4|offset2
	 */
	P_FILE_DATA = 11,
}

void DealMessage(const char* recvBuf, const int rLen, 
	const int sockfd = SOCKET_ERROR, const struct sockaddr* addr = NULL, const int alen = 0);

#endif
