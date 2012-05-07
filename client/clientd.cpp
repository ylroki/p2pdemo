#include "linux_header.h"
#include "socket_header.h"
#include "command.h"
#include "string_header.h"
#include "download_file.h"
#include "upload_file.h"
#include "file_system.h"
#include "kad.h"

bool g_DaemonStopped = true;
CDownloadFile g_DownloadFile("2781dea1445042e8e02fa7303bd53f5b");
CUploadFile g_UploadFile;
CConfig g_Config;
CFileSystem g_FileSystem;
CKad* g_Kad;
std::list<CDownloadFile*> g_Manager;

void DealLocalCommand(const char* command, char* response)
{
	if (strcmp(command, "stop") == 0)
	{
		g_DownloadFile.Stop();
		g_DaemonStopped = true;
	}
	else if (strcmp(command, "download") == 0)
	{
		g_DownloadFile.Start(&g_Config);
	}
	else if (strcmp(command, "current") == 0)
	{
		memset(response, 0, BUF_SIZE);
		KDownStatus ds;
		char percent;
		std::string md5;

		g_DownloadFile.GetDetail(ds, percent, md5);
		sprintf(response, "%s %d%% %d\n", md5.c_str(), percent, ds);

		std::list<CDownloadFile*>::iterator it;
		for (it = g_Manager.begin(); it != g_Manager.end(); ++it)
		{
			(*it)->GetDetail(ds, percent, md5);
			sprintf(response, "%s %d%% %d\n", md5.c_str(), percent, ds);
		}
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

	g_FileSystem.Start(&g_Config);
	g_UploadFile.Start(&g_Config);
	g_UploadFile.SetFileSystem(&g_FileSystem);
	g_Kad = new CKad(&g_Config, &g_FileSystem);
	g_Manager.clear();

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
				char response[BUF_SIZE] = "received";
				DealLocalCommand(buf, response);
				sendto(sockfd, response, strlen(response), 0, (struct sockaddr*)abuf, alen);
			}
		}

		//manager download file.
		std::list<CDownloadFile*>::iterator it;
		for (it = g_Manager.begin(); it != g_Manager.end();)
		{
			KDownStatus ds = (*it)->GetStatus();
			if (ds == DS_DONE || ds == DS_ERROR)	
				it = g_Manager.erase(it);
			else
				++it;
		}
		Sleep(100);
		
	}
	close(sockfd);
	
	std::list<CDownloadFile*>::iterator it;
	for (it = g_Manager.begin(); it != g_Manager.end(); ++it)
	{
		(*it)->Stop();
		delete (*it);
	}
	g_Manager.clear();
	delete g_Kad;
	g_UploadFile.Stop();
	g_FileSystem.Stop();
	return 0;
}


