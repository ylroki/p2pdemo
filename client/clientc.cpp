#include "linux_header.h"
#include "socket_header.h"
#include "command.h"
#include "string_header.h"
#include "config.h"

CConfig g_Config;

int main(int argc, char* argv[])
{
	// A Foreground process
	if (argc < 2)
		ErrorQuit("No argument");
	std::string configName = "config/client.conf";
	std::string cmd;
	if (strcmp(argv[1], "-c") == 0) 
	{
		// Has a config file.
		if (argc < 3)
			ErrorQuit("No config file.");
		if (access(argv[2], F_OK) == 0)
			configName = argv[1];
		if (argc < 4)
			ErrorQuit("No Command.");
		cmd = argv[3];
	}
	else
	{
		cmd = argv[1];
	}
	// Get network configuration.
	if (g_Config.Init(configName.c_str()) == false)
		ErrorQuit("Error on getting configuration.");
	int port = g_Config.GetLocalPort();

	// Send command to background process.
	int sockfd;	
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		ErrorQuit("Can't create socket");
	if (SendTo(sockfd, cmd.c_str(), NULL, port) == false)
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


