#include "linux_header.h"
#include "socket_header.h"
#include "command.h"
#include "string_header.h"
#include "download_file.h"
#include "upload_file.h"
#include "file_system.h"

bool g_DaemonStopped = true;
CDownloadFile g_DownloadFile("2781dea1445042e8e02fa7303bd53f5b");
CUploadFile g_UploadFile;
CConfig g_Config;
CFileSystem g_FileSystem;

void DealLocalCommand(const char* command)
{
	if (strcmp(command, "stop") == 0)
	{
		g_DownloadFile.Stop();
		g_DaemonStopped = true;
	}
	if (strcmp(command, "download") == 0)
	{
		g_DownloadFile.Start(&g_Config);
	}
}

int main(int argc, char* argv[])
{
	// Get network configuration.
	std::string configName = "config/client.conf";
	if (argc >= 2 && access(argv[1], F_OK) == 0)
	{
		configName = argv[1];
	}
	if (g_Config.Init(configName.c_str()) == false)
		ErrorQuit("Error on getting configuration ");

	int port = g_Config.GetLocalPort();
	
	// A daemon, bind to local address, listennig command.
	printf("Bind %s:%d\n", "127.0.0.1", port);
#ifndef __DEBUG__
	Daemonize();// Close all file descriptors include socket
#endif	
	int sockfd;	
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		ErrorQuit("Can't create socket");

	if (Bind(sockfd, NULL, port) == false)
		ErrorQuit("Can't bind socket");

	g_UploadFile.Start(&g_Config);
	g_FileSystem.Start(&g_Config);
	g_UploadFile.SetFileSystem(&g_FileSystem);

	g_DaemonStopped = false;
	while (!g_DaemonStopped)
	{
		fd_set rSet;
		FD_ZERO(&rSet);
		FD_SET(sockfd, &rSet);
		struct timeval t;
		t.tv_sec = 0;
		t.tv_usec = 100;
		if (select(sockfd + 1, &rSet, NULL, NULL, &t) > 0)
		{
			if (FD_ISSET(sockfd, &rSet))
			{
				// sockfd can be read.
				int n;
				char abuf[MAX_ADDR_SIZE];
				socklen_t alen = MAX_ADDR_SIZE;
				char buf[BUF_SIZE];
				memset(buf, 0, sizeof(buf));
				if ((n = recvfrom(sockfd, buf, BUF_SIZE, 0, (struct sockaddr*)abuf, &alen)) < 0)
					continue;
				const char* response = "Received";
				sendto(sockfd, response, strlen(response), 0, (struct sockaddr*)abuf, alen);
				DealLocalCommand(buf);
			}
		}
		Sleep(100);
		
	}
	close(sockfd);
	
	g_UploadFile.Stop();
	g_FileSystem.Stop();
	return 0;
}


