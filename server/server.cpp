#include "linux_header.h"
#include "socket_header.h"
#include "server_config.h"
#include "stream.h"
#include "database_header.h"
#include "md5_header.h"

CConfig g_Config;

unsigned long GetFileSize(CDatabase database, const char* md5)
{
	char sql[BUF_SIZE];
	sprintf(sql, "select size from filesize where md5='%s'", md5);
	char** res;
	int nRow = 0;
	int nCol = 0;
	database.GetTable(sql, &res, &nRow, &nCol);
	return atoi(res[nCol]);
}


int DealEachSource(void* arg, int nCol, char** result, char** name)
{
	CMemoryStream* stream = static_cast<CMemoryStream*>(arg);
	if (stream->GetSize() + 6 <= stream->GetMaxSize())
	{
		unsigned long ipv4 = atoi(result[0]);
		unsigned short port = atoi(result[1]);
		stream->WriteInteger<unsigned long>(htonl(ipv4));
		stream->WriteInteger<unsigned short>(htons(port));
	}
	return 0;
}

void ResponseSources(unsigned char* hexHash, unsigned long filesize, int n, char* srcBuf)
{
	char sendBuf[BUF_SIZE];
	CMemoryStream sender(sendBuf, 0, BUF_SIZE);
	sender.WriteInteger<char>(0x14);
	sender.WriteBuffer(hexHash, 16);
	sender.WriteInteger<unsigned long>(htonl(filesize));
	sender.WriteInteger<char>(n);
	sender.WriteBuffer(srcBuf, 6*n);
}

int main()
{
	if (g_Config.Init("config/server.conf") == false)
		ErrorQuit("Error config file");
	 
#ifndef __DEBUG__
	Daemonize();
#endif

	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (Bind(sock, NULL, g_Config.GetPort()) == false)
		ErrorQuit("Bind error");
	CDatabase database;
	database.Open("cache/server.db");
	database.CreateTable("hash", "(md5 TEXT, ipv4 INTEGER, port INTEGER, primary key(md5,ipv4,port))");
	database.CreateTable("filesize", "(md5 TEXT primary key, size INTEGER)");
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
					printf("Receive 0x01 command.\n");
					unsigned short port = ntohs(stream.ReadInteger<unsigned short>());
					unsigned long nHash = ntohl(stream.ReadInteger<unsigned long>());
					unsigned long ipv4 = ntohl(((struct sockaddr_in*)abuf)->sin_addr.s_addr);
					while (nHash--)
					{
						unsigned char hexHash[16];
						stream.ReadBuffer(hexHash, 16);
						unsigned long filesize = ntohl(stream.ReadInteger<unsigned long>());
						char md5[33];
						md5[32] = 0;
						Hex2MD5(hexHash, md5);
						char sql[BUF_SIZE];
						sprintf(sql, "insert into hash values('%s', %lu, %hu)",
									md5, ipv4, port);
						database.Execute(sql);
						sprintf(sql, "insert into filesize values('%s', %lu)",
									md5, filesize);
						database.Execute(sql);
					}
					break;
				}
			case 0x04:
				{
					//request sources
					unsigned char hexHash[16];
					stream.ReadBuffer(hexHash, 16);
					char md5[33];
					md5[32] = 0;
					Hex2MD5(hexHash, md5);
					char sql[BUF_SIZE];
					sprintf(sql, "select ipv4,port from hash where md5='%s'", md5);
					char srcBuf[BUF_SIZE - 100];
					CMemoryStream srcStream(srcBuf, 0, BUF_SIZE - 100);
					database.Execute(sql, DealEachSource, &srcStream);

					unsigned long filesize = GetFileSize(database, md5);
					ResponseSources(hexHash, filesize, srcStream.GetSize()/6, srcBuf);
					break;
				}
			default:
				{
					break;
				}
			}
		}

	}
	database.Close();
	return 0;	
}
