#ifndef __CLIENT_DOWNLOAD_FILE_H__
#define __CLIENT_DOWNLOAD_FILE_H__
#include "linux_header.h"
#include "socket_header.h"
#include "config.h"
#include "stream.h"
#include "md5_header.h"
#include "command.h"
#include "advanced_file.h"

class CProtocolManager;
class CKad;

enum KDownStatus
{
	DS_WAIT,
	DS_RUNNING,
	DS_DONE,
	DS_ERROR
};



class CDownloadFile
{
public:
	CDownloadFile(const char* md5);
	~CDownloadFile();
	KDownStatus GetStatus();
	bool Start(CConfig*);
	void Stop();
	void DealSourceResponse(const unsigned char* hexHash, unsigned long filesize,
		std::vector<TPeer>* vec);
	void DealCheckResult(const unsigned char* hexHash, unsigned long sessionID, char status);
	void DealFileData(const unsigned char* hexHash,
		unsigned long offset, const char* src, unsigned long size);
	void SetKad(CKad* kad);
	void GetDetail(KDownStatus& status, char& percent, std::string& md5,
		time_t& past, unsigned short& speed);
	void SetFilename(const char* name);

private:
	static void* ThreadFunc(void* arg);
	void Work();
	void RequestSources();
	void UpdateSources();
	void RequestFileData(TPeer peer);
	bool InitSocket();
	void SelectSocket();
	void RecvMessage();

	std::string m_MD5;
	std::string m_Filename;
	KDownStatus m_Status;
	pthread_t m_Thread;
	int m_Socket;
	std::vector<TPeer> m_VecSource;
	std::list<TPeer> m_WorkSource;
	CConfig* m_Config;
	CProtocolManager* m_Protocol;
	CAdvancedFile* m_AdFile;
	CKad* m_Kad;
	std::map<unsigned long, time_t> m_Ticker;
	std::map<unsigned long, time_t> m_Session;

	unsigned short m_Speed;
	time_t m_StartTime;
	time_t m_PastTime;
	time_t m_Clock;
	unsigned long m_LastSecBlock;
};

#endif
