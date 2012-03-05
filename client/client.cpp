#include "linux_header.h"
#include "socket_header.h"
#include "daemonize.h"


int main()
{
	// Get network configuration.
	FILE* file = fopen("config/client.conf", "r");
	if (file == NULL)
		ErrorQuit("No client.conf");
	
	std::string ipString = "127.0.0.1";
	char buf[BUF_SIZE];
	if (fgets(buf, BUF_SIZE, file) == NULL)
		ErrorQuit("No IP address");
	
	int port = 31415;
	if (fgets(buf, BUF_SIZE, file) == NULL)
		ErrorQuit("No port");
	
	fclose(file);


#ifdef __CLIENT_DAEMON__
	// A daemon, bind to local address, listennig command.
	Daemonize();// Close all file descriptors include socket
	
	int sockfd;	
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		ErrorQuit("Can't create socket");

	if (Bind(sockfd, ipString.c_str(), port) == false)
		ErrorQuit("Can't bind socket");

	int n;
	char abuf[MAX_ADDR_SIZE];
	socklen_t alen = MAX_ADDR_SIZE;
	if ((n = recvfrom(sockfd, buf, BUF_SIZE, 0, (struct sockaddr*)abuf, &alen)) < 0)
		exit(1);
	sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)abuf, alen);

#else
	int sockfd;	
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		ErrorQuit("Can't create socket");
	if (SendTo(sockfd, "hello", ipString.c_str(), port) == false)
		ErrorQuit("sendto error");
	int n;
	if ((n = recv(sockfd, buf, BUF_SIZE, 0)) < 0)
		ErrorQuit("recv error");
	printf("%s",  buf);

#endif
	close(sockfd);
	return 0;
}


