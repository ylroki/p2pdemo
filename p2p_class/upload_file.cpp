#include "upload_file.h"

CUploadFile::CUploadFile()
	:m_Thread(THREAD_ERROR),
	m_Stopped(true),
	m_Socket(SOCKET_ERROR),
	m_Config(NULL),
	m_Protocol(NULL),
	m_FileSystem(NULL)
{
}

CUploadFile::~CUploadFile()
{}


bool CUploadFile::Start(CConfig* config)
{
	if (!m_Stopped)
		return true;
	m_Config = config;
	m_Protocol = new CProtocolManager(config);
	if (InitSocket() == false)
		return false;
		
	m_Stopped = false;
	if (0 == pthread_create(&m_Thread, NULL, ThreadFunc, this))
		return true;		
	m_Stopped = true;
	return false;
}

void CUploadFile::Stop()
{
	m_Stopped = true;
	if (m_Thread != THREAD_ERROR)
		pthread_join(m_Thread, NULL);
	if (m_Protocol)
		delete m_Protocol;
	if (m_Socket != SOCKET_ERROR)
		close(m_Socket);
}

void CUploadFile::SetFileSystem(CFileSystem* fs)
{
	m_FileSystem = fs;
}

void* CUploadFile::ThreadFunc(void* arg)
{
	CUploadFile* up = static_cast<CUploadFile*>(arg);
	up->Work();
	return ((void*)0);
}

void CUploadFile::Work()
{
	if (m_Socket == SOCKET_ERROR)
		return;
	int maxFd = m_Socket + 1;
	struct timeval t;
	t.tv_sec = 0;
	t.tv_usec = 100;
	printf("Upload thread work\n");
	while (!m_Stopped)	
	{
		fd_set rSet;
		FD_ZERO(&rSet);
		FD_SET(m_Socket, &rSet);
		if (select(maxFd, &rSet, NULL, NULL, &t))
		{
			if (FD_ISSET(m_Socket, &rSet))
			{
				RecvMessage();
			}
		}
		Sleep(100);
	}
	printf("Upload thread stop\n");
}

bool CUploadFile::InitSocket()
{
	if ((m_Socket = socket(AF_INET, SOCK_DGRAM, 0)) == SOCKET_ERROR)
		return false;
	printf("%d\n", m_Socket);
		
	return Bind(m_Socket, NULL, m_Config->GetPeerPort());
}

void CUploadFile::RecvMessage()
{
	m_Protocol->Response(m_Socket, this);
}

bool CUploadFile::IsExist(const unsigned char* hexHash)
{
	return m_FileSystem->IsExist(hexHash);
}

unsigned long CUploadFile::GetFileData(const unsigned char* hexHash, 
	unsigned long offset, unsigned long size, char* dst)
{
	std::string pathname = m_FileSystem->GetPath(hexHash);
	if (access(pathname.c_str(), F_OK) == 0)
	{
		CFileStream file(pathname.c_str(), O_RDONLY);
		return file.Read(offset, dst, size);
	}
	return 0;
}
