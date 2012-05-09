#include "kad_protocol.h"
#include "kad.h"
#include "task_manager.h"
#include "route_table.h"
#include "command.h"

CKadProtocol::CKadProtocol(CKad* kad)
	:m_Kad(kad)
{}

CKadProtocol::~CKadProtocol()
{}

void CKadProtocol::RecvMessage(int sockfd)
{
	if (sockfd == SOCKET_ERROR)	
		return ;
	char abuf[MAX_ADDR_SIZE];
	socklen_t alen = MAX_ADDR_SIZE;
	char buf[BUF_SIZE];
	memset(buf, 0, sizeof(buf));
	int n = recvfrom(sockfd, buf, BUF_SIZE, 0, (struct sockaddr*)abuf, &alen);
	if (n > 0)
	{
		// In each package, first three object is cmd, remoteID, taskID.
		CMemoryStream reader(buf, n, BUF_SIZE);
		char cmd = reader.ReadInteger<char>();
		unsigned char remoteHex[16];
		reader.ReadBuffer(remoteHex, 16);
		CUInt128 remoteID = CUInt128::FromHex(remoteHex);
		unsigned long remoteIP = ntohl(((struct sockaddr_in*)abuf)->sin_addr.s_addr);
		unsigned short remotePort = ntohs(((struct sockaddr_in*)abuf)->sin_port);
		m_Kad->AddNode(remoteID, remoteIP, remotePort); //Add remote infomation in route table.
		short taskID = ntohs(reader.ReadInteger<short>());

		// Get self ID.
		unsigned char selfID[16];
		m_Kad->GetClientIDHex(selfID);
		printf("kad recv %d\n", cmd);
		switch (cmd)
		{
		case 0x40://ping request
			{
				char sendBuf[BUF_SIZE];
				CMemoryStream sender(sendBuf, 0, BUF_SIZE);
				sender.WriteInteger<char>(0x41);
				sender.WriteBuffer(selfID, 16);
				sender.WriteInteger<short>(htons(taskID));
				sendto(sockfd, sendBuf, sender.GetSize(), 0, (struct sockaddr*)abuf, alen);
				break;
			}
		case 0x41:// ping response
			{
				m_Kad->GetTaskManager()->Process(taskID);
				break;
			}
		case 0x42://store request
			{
				unsigned char keyHex[16];
				reader.ReadBuffer(keyHex, 16);
				CUInt128 key = CUInt128::FromHex(keyHex);
				unsigned long ip = ntohl(reader.ReadInteger<unsigned long>());
				unsigned short port = ntohs(reader.ReadInteger<unsigned short>());
				unsigned long size = ntohl(reader.ReadInteger<unsigned long>());
				m_Kad->AddKeyValue(key, ip, port, size);
				break;
			}
		case 0x44://find node request
			{
				unsigned char targetHex[16];
				reader.ReadBuffer(targetHex, 16);
				CUInt128 target = CUInt128::FromHex(targetHex);

				char sendBuf[BUF_SIZE];
				CMemoryStream sender(sendBuf, 0, BUF_SIZE);
				sender.WriteInteger<char>(0x45);
				sender.WriteBuffer(selfID, 16);
				sender.WriteInteger<short>(htons(taskID));
					
				FillNodesCloseTo(target, &sender);
				
				sendto(sockfd, sendBuf, sender.GetSize(), 0, (struct sockaddr*)abuf, alen);
				break;
			}
		case 0x45://find node response
			{
				size_t number = reader.ReadInteger<char>();
				std::list<TNode> nodes;
				while (number--)
				{
					TNode node;
					node.IPv4 = IPLong2String(ntohl(reader.ReadInteger<unsigned long>()));
					node.Port = ntohs(reader.ReadInteger<unsigned short>());
					unsigned char hex[16];
					reader.ReadBuffer(hex, 16);
					node.NodeID = CUInt128::FromHex(hex);
				}
				//Insert remote node at the front of list.
				TNode node;
				node.NodeID = remoteID;//just ID is OK.
				nodes.push_front(node);
				m_Kad->GetTaskManager()->Process(taskID, &nodes);
				break;
			}
		case 0x46://find value request
			{
				unsigned char targetHex[16];
				reader.ReadBuffer(targetHex, 16);
				CUInt128 target = CUInt128::FromHex(targetHex);
				
				char sendBuf[BUF_SIZE];
				CMemoryStream sender(sendBuf, 0, BUF_SIZE);
				std::vector<TPeer> source;
				unsigned long filesize;
				if (m_Kad->FindSource(targetHex, &filesize, &source, false))
				{
					//I know value of key.
					sender.WriteInteger<char>(0x47);
					sender.WriteBuffer(selfID, 16);
					sender.WriteInteger<short>(htons(taskID));
					// key and values
					sender.WriteBuffer(targetHex, 16);
					char nVal = source.size() < 50 ? source.size() : 50;
					sender.WriteInteger<char>(nVal);
					sender.WriteInteger<unsigned long>(filesize);
					for (size_t i = 0; i < nVal; ++i)
					{
						TPeer peer = source[i];
						sender.WriteInteger<unsigned long>(htonl(IPString2Long(peer.IPv4.c_str())));
						sender.WriteInteger<unsigned short>(htons(peer.Port));
					}
				}	
				else
				{
					//I don't know value of key ,return 0x45
					sender.WriteInteger<char>(0x45);
					sender.WriteBuffer(selfID, 16);
					sender.WriteInteger<short>(htons(taskID));
					FillNodesCloseTo(target, &sender);
				}
				sendto(sockfd, sendBuf, sender.GetSize(), 0, (struct sockaddr*)abuf, alen);
				break;
			}
		case 0x47://find value response
			{
				m_Kad->GetTaskManager()->Process(taskID, NULL);	//arg is null, task will end.

				unsigned char keyHex[16];
				reader.ReadBuffer(keyHex, 16);
				CUInt128 key = CUInt128::FromHex(keyHex);
				char nVal = reader.ReadInteger<char>();
				unsigned long filesize = ntohl(reader.ReadInteger<unsigned long>());
				while (nVal--)
				{
					unsigned long ip = ntohl(reader.ReadInteger<unsigned long>());
					unsigned short port = ntohl(reader.ReadInteger<unsigned short>());
					m_Kad->AddKeyValue(key, ip, port, filesize);
				}
				break;
			}
		default:
			{
				break;
			}
		}
	}
}

void CKadProtocol::FillNodesCloseTo(CUInt128 target, CMemoryStream* sender)
{
	std::list<TNode> closeNode;
	m_Kad->GetRouteTable()->GetCloseTo(target, &closeNode);
	
	// remove nodes which is more far from target then client.
	std::list<TNode>::iterator it;
	CUInt128 distance = m_Kad->GetClientID() ^ target;
	for (it = closeNode.begin(); it != closeNode.end();)
	{
		if ((it->NodeID^target) > distance)
			it = closeNode.erase(it);
		else
			++it;
	}
	sender->WriteInteger<char>(closeNode.size());
	for (it = closeNode.begin(); it != closeNode.end(); ++it)
	{
		unsigned long ip = IPString2Long(it->IPv4.c_str());
		unsigned short port = it->Port;
		unsigned char hex[16];
		it->NodeID.ToHex(hex);
		sender->WriteInteger<unsigned long>(htonl(ip));
		sender->WriteInteger<unsigned short>(htons(port));
		sender->WriteBuffer(hex, 16);
	}
}
