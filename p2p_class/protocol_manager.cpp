#include "protocol_manager.h"

CProtocolManager::CProtocolManager(CConfig* config)
	:m_Config(config)
{}

CProtocolManager::~CProtocolManager()
{}

void CProtocolManager::AddHash(unsigned char* hexHash)
{
	vecHashes.insert(vecHashes.end(), hexHash, hexHash+20);		
}

const int g_NHashes = 50;
void CProtocolManager::SendCommand(char id, int sockfd, ...)
{
	if (sockfd == SOCKET_ERROR)
		sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	switch (id)
	{
	case 0x01:
		{
			char buf[BUF_SIZE];
			for (size_t i = 0 ; i < vecHashes.size(); i+=g_NHashes*20)
			{
				int n = Min(g_NHashes, (vecHashes.size() - i)/20);
				CMemoryStream stream(buf, 0, BUF_SIZE);
				stream.WriteInteger<char>(0x01);
				stream.WriteInteger<unsigned short>(htons(m_Config->GetPeerPort()));
				stream.WriteInteger<unsigned long>(htonl(n));
				stream.WriteBuffer(&(vecHashes[i]), n*20);
				SendTo(sockfd, buf, stream.GetSize(), 
					m_Config->GetServerIP().c_str(), m_Config->GetServerPort());
			}
			break;
		}
	case 0x21:
		{
			// Check if file is exist or not.
			va_list ap;
			va_start(ap, sockfd);
			const char* md5 = va_arg(ap, const char*);
			unsigned char hexHash[16];
			MD52Hex(md5, hexHash);
			TPeer* peer = va_arg(ap, TPeer*);
			char buf[BUF_SIZE];
			CMemoryStream stream(buf, 0, BUF_SIZE);
			stream.WriteInteger<char>(id);
			stream.WriteBuffer(hexHash, 16);
			stream.WriteInteger<unsigned long>(htonl(peer->SessionID));
			SendTo(sockfd, buf, stream.GetSize(), peer->IPv4.c_str(), peer->Port);
			va_end(ap);
			break;
		}
	case 0x22:
		{
			va_list	ap;
			va_start(ap, sockfd);
			TPeer* peer = va_arg(ap, TPeer*);
			const char* md5 = va_arg(ap, const char*);
			unsigned long st_blk = va_arg(ap, unsigned long);
			unsigned long ed_blk = va_arg(ap, unsigned long);
			
			unsigned char hexHash[16];
			MD52Hex(md5, hexHash);
			char buf[BUF_SIZE];
			CMemoryStream sender(buf, 0, BUF_SIZE);
			sender.WriteInteger<char>(0x22);
			sender.WriteBuffer(hexHash, 16);
			sender.WriteInteger<unsigned long>(htonl(st_blk));
			sender.WriteInteger<unsigned long>(htonl(ed_blk));
			SendTo(sockfd, buf, sender.GetSize(), peer->IPv4.c_str(), peer->Port);
			va_end(ap);
			break;
		}
	default:
		{
			 break;
		}
	}
}

void CProtocolManager::Response(int sockfd, void* arg)
{
	if (sockfd == SOCKET_ERROR)
		return ;
	char abuf[MAX_ADDR_SIZE];
	socklen_t alen = MAX_ADDR_SIZE;
	char buf[BUF_SIZE * 8];
	memset(buf, 0, sizeof(buf));
	int n = recvfrom(sockfd, buf, BUF_SIZE, 0, (struct sockaddr*)abuf, &alen);
	if (n > 0)
	{
		CMemoryStream reader(buf, n, BUF_SIZE * 2);
		char id = reader.ReadInteger<char>();
		switch (id)
		{
		case 0x14:
			{// server sends sources back.
				unsigned char hexHash[16];
				reader.ReadBuffer(hexHash, 16);
				unsigned long filesize = ntohl(reader.ReadInteger<unsigned long>());
				int nSrc = reader.ReadInteger<char>();
				std::vector<TPeer> vecSource;
				while (nSrc--)
				{
					unsigned long ip = reader.ReadInteger<unsigned long>();
					unsigned short port = reader.ReadInteger<unsigned short>();
					struct in_addr ia;
					ia.s_addr= ip;
					struct TPeer peer;
					peer.IPv4 = inet_ntoa(ia);
					peer.Port = ntohs(port);
					peer.SessionID = ntohl(ip);
					vecSource.push_back(peer);
					printf("request result, Source:%s, %hu\n", peer.IPv4.c_str(), peer.Port);
				}
				CDownloadFile* down = static_cast<CDownloadFile*>(arg);
				down->DealSourceResponse(hexHash, filesize, &vecSource);
				break;
			}
		case 0x21:
			{
				// Check if file exists or not.
				printf("check\n");
				unsigned char hexHash[16];
				reader.ReadBuffer(hexHash, 16);
				unsigned long sessionID = reader.ReadInteger<unsigned long>();
				CUploadFile* upload = static_cast<CUploadFile*>(arg);
				bool flag = upload->IsExist(hexHash);

				char sendBuf[BUF_SIZE];
				CMemoryStream sender(sendBuf, 0, BUF_SIZE);
				sender.WriteInteger<char>(0x31);
				sender.WriteBuffer(hexHash, 16);
				sender.WriteInteger<unsigned long>(sessionID);
				sender.WriteInteger<char>(flag);
				sendto(sockfd, sendBuf, sender.GetSize(), 0, (struct sockaddr*)abuf, alen);
				break;
			}
		case 0x22:
			{
				//Get file data.
				CUploadFile* upload = static_cast<CUploadFile*>(arg);
				unsigned char hexHash[16];
				reader.ReadBuffer(hexHash, 16);
				unsigned long st_blk = ntohl(reader.ReadInteger<unsigned long>());
				unsigned long ed_blk = ntohl(reader.ReadInteger<unsigned long>());
				unsigned long offset = st_blk * BLOCK_SIZE;
				unsigned long size = (ed_blk - st_blk + 1) * BLOCK_SIZE;
				char* dataBuf = new char[size];
				unsigned long fSize = upload->GetFileData(hexHash, offset, size, dataBuf);
				printf("get file data, byte offset:%lu byte size:%lu\n", offset, size);

				char* sendBuf = new char[size + BUF_SIZE];
				CMemoryStream sender(sendBuf, 0, size+ BUF_SIZE);
				sender.WriteInteger<char>(0x32);
				sender.WriteBuffer(hexHash, 16);
				sender.WriteInteger<unsigned long>(htonl(st_blk));
				sender.WriteInteger<unsigned long>(htonl(fSize));
				sender.WriteBuffer(dataBuf, fSize);

				sendto(sockfd, sendBuf, sender.GetSize(), 0, (struct sockaddr*)abuf, alen);
				delete sendBuf;
				delete dataBuf;
				break;
			}
		case 0x31:
			{
				// Check result return.
				unsigned char hexHash[16];
				reader.ReadBuffer(hexHash, 16);
				unsigned long sessionID = ntohl(reader.ReadInteger<unsigned long>());
				char status = reader.ReadInteger<char>();
				printf("check result:%d\n", status);

				CDownloadFile* down = static_cast<CDownloadFile*>(arg);
				down->DealCheckResult(hexHash, sessionID, status);
				break;
			}
		case 0x32:
			{
				// File data.
				unsigned char hexHash[16];
				reader.ReadBuffer(hexHash, 16);
				unsigned long offset = ntohl(reader.ReadInteger<unsigned long>());
				unsigned long size = ntohl(reader.ReadInteger<unsigned long>());
				printf("file data, block offset:%lu byte size:%lu\n", offset, size);
				char* dataBuf = new char[size];
				reader.ReadBuffer(dataBuf, size);
				CDownloadFile* down = static_cast<CDownloadFile*>(arg);
				down->DealFileData(hexHash, offset, dataBuf, size);
				delete dataBuf;
				break;	
			}
		default:
			{
				break;
			}
		}
	}
}
