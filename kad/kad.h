#ifndef __KAD_KAD_H__
#define __KAD_KAD_H__
#include "linux_header.h"
#include "socket_header.h"
#include "config.h"
#include "auto_lock.h"
#include "md5_header.h"
#include "database_header.h"
#include "command.h"

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
	unsigned long GetFileSize(CDatabase database, const char* md5);
	static int DealEachSource(void* arg, int nCol, char** result, char** name);

	CConfig* m_Config;
	bool m_Stopped;
	pthread_t m_WorkThread;
	pthread_t m_ListenThread;
	std::queue<std::string> m_QuePendingKeys;
	CLock m_KeyLock;
	CDatabase m_Database;
};
#endif
