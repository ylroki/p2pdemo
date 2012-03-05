#ifndef __INCLUDE_SOCKET_HEADER_H__
#define __INCLUDE_SOCKET_HEADER_H__
#include <sys/socket.h>

bool FillAddress(struct sockaddr_in& addr, const char* ipString, const int port, int domain = AF_INET)
{
	addr.sin_family = domain;
	addr.sin_port = htons(port);
	if (inet_pton(domain, ipString, &addr.sin_addr) != 1)
		return false;
	return true;
}

bool Bind(const int sockfd, const char* ipString, const int port)
{
	struct sockaddr_in addr;
	if (FillAddress(addr, ipString, port) == false)
		return false;
	
	if (bind(sockfd, (sockadd*)&addr, sizeof(addr)) == -1)
		return false;

	return true;
}

bool Connect(const int sockfd, const char* ipString, const int port)
{
	struct sockaddr_in addr;
	if (FillAddress(addr, ipString, port) == false)
		return false;
	
	if (connect(sockfd, (sockadd*)&addr, sizeof(addr)) == -1)
		return false;

	return true;
}

#endif
