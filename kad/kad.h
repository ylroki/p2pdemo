#ifndef __KAD_KAD_H__
#define __KAD_KAD_H__
#include "linux_header.h"
#include "socket_header.h"
#include "config.h"
#include "auto_lock.h"
#include "md5_header.h"
#include "database_header.h"
#include "command.h"
#include "define.h"
#include "file_system.h"
#include "uint128.h"
class CKadProtocol;
class CTaskManager;
class CRouteTable;
struct TNode;

class CKad
{
public:
	CKad(CConfig* config, CFileSystem* filesystem);
	~CKad();
	bool Start();
	void Stop();
	void FindSource(const unsigned char* key, unsigned long* filesize, std::vector<TPeer>* source);
	void AddNode(CUInt128 remoteID, unsigned long remoteIP, unsigned short remotePort);
	CTaskManager* GetTaskManager();
	void GetClientIDHex(unsigned char* hex);
	CRouteTable* GetRouteTable();
	int GetSocket();

private:
	static void* WorkThread(void* arg);
	void Work();
	bool InitSocket();
	void SelectSocket();
	void JoinKad();
	void Republish();
	void Refresh();
	unsigned long GetFileSize(CDatabase database, const char* md5);
	static int DealEachSource(void* arg, int nCol, char** result, char** name);
	static int RepublishHelper(void* arg, int nCol, char** result, char** name);
	CUInt128 CalculateClientID();
	void UpdateSelfKey();

	CConfig* m_Config;
	bool m_Stopped;
	pthread_t m_WorkThread;
	pthread_t m_ListenThread;
	CLock m_KeyLock;
	CDatabase m_Database;
	CRouteTable* m_RouteTable;
	CUInt128 m_ClientID;
	time_t m_LastRepublish;
	time_t m_LastRefresh;
	CTaskManager* m_TaskManager;
	CFileSystem* m_FileSystem;
	int m_Socket;	
	CKadProtocol* m_Protocol;
};
#endif
