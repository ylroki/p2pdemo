#ifndef __CLIENT_FILE_SYSTEM_H__
#define __CLIENT_FILE_SYSTEM_H__
#include "linux_header.h"
#include "socket_header.h"
#include "config.h"
#include "database_header.h"
#include "md5_header.h"
#include "protocol_manager.h"
class CProtocolManager;
class CFileSystem
{
public:
	CFileSystem();
	~CFileSystem();
	bool Start(CConfig*);
	void Stop();
	bool IsExist(const unsigned char* hexHash);
	unsigned long GetFileSize(const unsigned char* hexHash);
	std::string GetPath(const char* md5);
	std::string GetPath(const unsigned char* hexHash);
	void GetAllHashes(std::map<std::string, unsigned long>* keys);

private:
	static void* ThreadFunc(void* arg);
	static int GetAllHashesHelper(void* arg, int nCol, char** result, char** name);
	void Work();
	void FindResources();
	void DealFile(const std::string file, CProtocolManager* protocol);

	pthread_t m_Thread;
	bool m_Stopped;
	CConfig* m_Config;
	unsigned int m_PastTime;
	CDatabase m_Database;
};

#endif
