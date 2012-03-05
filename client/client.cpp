#include "linux_header.h"
#include "socket_header.h"
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
	printf("IP: %s", buf);

	int port = 31415;
	if (fgets() == NULL)
		ErrorQuit("No port");
	printf("port: %s", buf);
	
	fclose(file);


	// Bind to local address, listennig command.
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0) == -1)
		ErrorQuit("Can't create socket");
	if (Bind(sockfd, ipString.c_str(), port) == false)
		ErrorQuit("Can't bind socket");
	
	Daemonize();
	
	int n;
	char abuf[MAX_ADDR_LEN];
	socklen_t alen = MAX_ADDR_LEN;
	if ((n = recvfrom(sockfd, buf, BUF_SIZE, 0, (struct sockaddr*)abuf, &alen)) < 0)
		exit(1);
	sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)abuf, alen);
	close(sockfd);
	return 0;
}
