#ifndef __INCLUDE_SOCKET_HEADER_H__
#define __INCLUDE_SOCKET_HEADER_H__
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX_ADDR_SIZE 256

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
	
	if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
		return false;

	return true;
}

bool Connect(const int sockfd, const char* ipString, const int port)
{
	struct sockaddr_in addr;
	if (FillAddress(addr, ipString, port) == false)
		return false;
	
	if (connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
		return false;

	return true;
}

bool SendTo(int sockfd, const std::string buf, const char* ipString, const int port)
{
	struct sockaddr_in addr;
	if (FillAddress(addr, ipString, port) == false)
		return false;
	if (sendto(sockfd, buf.c_str(), buf.size(), 0, (struct sockaddr*)&addr, sizeof(addr)) == -1)
		return false;
	return true;
}
#endif
