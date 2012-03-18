#include "linux_header.h"
#include "socket_header.h"
#include "command.h"
#include "string_header.h"
#include "config.h"

CConfig g_Config;

int main(int argc, char* argv[])
{
	// Get network configuration.
	if (g_Config.Init("config/client.conf") == false)
		ErrorQuit("Error on getting configuration ");
	std::string ipString = g_Config.GetLocalIP();
	int port = g_Config.GetLocalPort();
	
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
	char buf[BUF_SIZE];
	memset(buf, 0, sizeof(buf));
	if ((n = recv(sockfd, buf, BUF_SIZE, 0)) < 0)
		ErrorQuit("recv() error");
	printf("%s\n",  buf);
	close(sockfd);

	return 0;
}


