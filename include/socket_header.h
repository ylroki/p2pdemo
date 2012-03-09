#ifndef __INCLUDE_SOCKET_HEADER_H__
#define __INCLUDE_SOCKET_HEADER_H__
#include "linux_header.h"
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX_ADDR_SIZE 256
#define SOCKET_ERROR -1


bool FillAddress(struct sockaddr_in& addr, const char* ipString, const int port, int domain = AF_INET);

bool Bind(const int sockfd, const char* ipString, const int port);

bool Connect(const int sockfd, const char* ipString, const int port);

bool SendTo(int sockfd, const std::string buf, const char* ipString, const int port);

#endif
