#ifndef __KAD_KAD_H__
#define __KAD_KAD_H__
#include "linux_header.h"
#include "socket_header.h"
#include "config.h"
#include "auto_lock.h"
#include "md5_header.h"
#include "database_header.h"
#include "command.h"
#include "route_table.h"
#include "define.h"
#include "task_manager.h"
struct TNode;
class CRouteTable;

class CKad
{
public:
	CKad(CConfig* config);
	~CKad();
	bool Start();
	void Stop();
	void FindSource(const unsigned char* key, unsigned long* filesize, std::vector<TPeer>* source);

private:
	static void* WorkThread(void* arg);
	void Work();
	static void* ListenThread(void* arg);
	void Listen();
	void JoinKad();
	void Republish();
	void Refresh();
	unsigned long GetFileSize(CDatabase database, const char* md5);
	static int DealEachSource(void* arg, int nCol, char** result, char** name);
	static int RepublishHelper(void* arg, int nCol, char** result, char** name);
	CUInt128 CalculateClientID();

	CConfig* m_Config;
	bool m_Stopped;
	pthread_t m_WorkThread;
	pthread_t m_ListenThread;
	std::queue<std::string> m_QuePendingKeys;
	CLock m_KeyLock;
	CDatabase m_Database;
	CRouteTable* m_RouteTable;
	CUInt128 m_ClientID;
	time_t m_LastRepublish;
	time_t m_LastRefresh;
	CTaskManager* m_TaskManager;
};
#endif
