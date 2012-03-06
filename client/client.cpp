#include "linux_header.h"
#include "socket_header.h"
#include "daemonize.h"
#include "command.h"
#include "string_header.h"


int main(int argc, char* argv[])
{
	// Get network configuration.
	FILE* file = fopen("config/client.conf", "r");
	if (file == NULL)
		ErrorQuit("No client.conf");
	
	char buf[BUF_SIZE];
	if (fgets(buf, BUF_SIZE, file) == NULL)
		ErrorQuit("No IP address");
	std::string ipString = buf;
	ipString = TrimString(ipString);
	
	if (fgets(buf, BUF_SIZE, file) == NULL)
		ErrorQuit("No port");
	int port = atoi(buf);
	
	fclose(file);

#ifdef __CLIENT_DAEMON__
	// A daemon, bind to local address, listennig command.
	printf("Bind %s:%d\n", ipString.c_str(), port);

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
	const char* response = "Received";
	sendto(sockfd, response, strlen(response), 0, (struct sockaddr*)abuf, alen);
	close(sockfd);

#else
	// A Foreground process
	if (argc < 2)
		ErrorQuit("No argument");
	if (!IsLocalCommand(argv[1]))
		ErrorQuit("Invalid command");

	// Send command to background process.
	int sockfd;	
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		ErrorQuit("Can't create socket");
	if (SendTo(sockfd, argv[1], ipString.c_str(), port) == false)
		ErrorQuit("sendto() error");
	int n;
	memset(buf, 0, sizeof(buf));
	if ((n = recv(sockfd, buf, BUF_SIZE, 0)) < 0)
		ErrorQuit("recv() error");
	printf("%s\n",  buf);
	close(sockfd);

#endif
	return 0;
}


