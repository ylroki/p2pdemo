#include "linux_header.h"
#include "socket_header.h"
#include "server_config.h"
#include "stream.h"
#include "database_header.h"
#include "md5_header.h"

CConfig g_Config;

int main()
{
	if (g_Config.Init("config/server.conf") == false)
		ErrorQuit("Error config file");
	 
	Daemonize();

	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (Bind(sock, NULL, g_Config.GetPort()) == false)
		ErrorQuit("Bind error");
	CDatabase database;
	database.Open("cache/server.db");
	database.CreateTable("hash", "(md5 TEXT, ipv4 TEXT, port INTEGER)");
	while (true)
	{
		char abuf[MAX_ADDR_SIZE];
		socklen_t alen;
		char buf[BUF_SIZE];
		int n;
		if ((n = recvfrom(sock, buf, BUF_SIZE, 0, (struct sockaddr*)abuf, &alen)) > 0)
		{
			CMemoryStream stream(buf, n);
			char id = stream.ReadInteger<char>();
			switch (id)
			{
			case 0x01:
				{
					unsigned short port = ntohs(stream.ReadInteger<unsigned short>());
					unsigned long nHash = ntohl(stream.ReadInteger<unsigned long>());
					unsigned long ipv4 = ntohl(((struct sockaddr_in*)abuf)->sin_addr.s_addr);
					while (nHash--)
					{
						unsigned char hexHash[16];
						stream.ReadBuffer(hexHash, 16);
						char md5[33];
						md5[32] = 0;
						Hex2MD5(hexHash, md5);
						char sql[BUF_SIZE];
						sprintf(sql, "insert into hash values('%s', %lu, %hu)",
									md5, ipv4, port);
						database.Execute(sql);
					}
				}
			}
		}

	}
	database.Close();
	return 0;	
}
