#include "linux_header.h"
#include "socket_header.h"
#include "config.h"

CConfig g_Config;

int main()
{
	if (g_Config.Init("config/server.conf") == false)
		ErrorQuit("Error config file");
	 
	Daemonize();

	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (Bind(sock, NULL, g_Config.GetPort()) == false)
		ErrorQuit("Bind error");
	
	while (true)
	{
		char abuf[MAX_ADDR_SIZE];
		socklen_t alen;
		char buf[BUF_SIZE];
		int n;
		if ((n = recvfrom(sock, buf, BUF_SIZE, 0, (struct sockaddr*)abuf, &alen)) > 0)
		{
			// TODO: Deal recv message
		}

	}
	return 0;	
}
