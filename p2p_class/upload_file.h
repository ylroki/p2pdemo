#ifndef __CLIENT_UPLOAD_FILE_H__
#define __CLIENT_UPLOAD_FILE_H__
#include "linux_header.h"
#include "socket_header.h"
#include "config.h"
#include "file_system.h"
#include "protocol_manager.h"

class CFileSystem;
class CProtocolManager;

class CUploadFile
{
public:
	CUploadFile();
	~CUploadFile();
	bool Start(CConfig* config);
	void Stop();
	void SetFileSystem(CFileSystem* fs);
	bool IsExist(const unsigned char* hexHash);

private:
	static void* ThreadFunc(void* arg);
	void Work();
	bool InitSocket();
	void RecvMessage();

	pthread_t m_Thread;
	bool m_Stopped;
	int m_Socket;
	CConfig* m_Config;
	CProtocolManager* m_Protocol;
	CFileSystem* m_FileSystem;
};

#endif
