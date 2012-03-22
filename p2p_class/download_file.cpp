#include "download_file.h"

CDownloadFile::CDownloadFile(const char* md5)
	:m_Status(DS_WAIT),
	m_Thread(THREAD_ERROR),
	m_Socket(SOCKET_ERROR),
	m_Config(NULL),
	m_MD5(md5),
	m_Protocol(NULL)
{
	m_VecSource.clear();	
}

CDownloadFile::~CDownloadFile()
{
	m_VecSource.clear();	
}

KDownStatus CDownloadFile::GetStatus()
{
	return m_Status;
}

bool CDownloadFile::Start(CConfig* config)
{
	m_Config = config;
	m_Protocol = new CProtocolManager(config);
	if (m_Status == DS_RUNNING)
		return true;
	m_Status = DS_RUNNING;
	if (0 == pthread_create(&m_Thread, NULL, ThreadFunc, this))
		return true;		
	m_Status = DS_ERROR;
	return false;
}

void CDownloadFile::Stop()
{
	m_Status = DS_DONE;
	if (m_Thread != THREAD_ERROR)
		pthread_join(m_Thread, NULL);
	
	if (m_Protocol)
		delete m_Protocol;
}

void* CDownloadFile::ThreadFunc(void* arg)
{
	CDownloadFile* down = static_cast<CDownloadFile*>(arg);
	down->Work();
	return ((void*)0);
}

void CDownloadFile::Work()
{
	if (InitSocket() == false)
		m_Status = DS_ERROR;	
	while (m_Status == DS_RUNNING)	
	{
		RequestSources();
		UpdateSources();
		SelectSocket();
		Sleep(100);
	}
}
const int g_LowerBoundOfSources = 5;
void CDownloadFile::RequestSources()
{
	if (m_VecSource.size() < g_LowerBoundOfSources)
	{
		char buf[BUF_SIZE];
		CMemoryStream stream(buf, 0);
		stream.WriteInteger<char>(0x04);
		unsigned char hexHash[16];
		MD52Hex(m_MD5.c_str(), hexHash);
		stream.WriteBuffer(hexHash, 16);
		SendTo(m_Socket, buf, stream.GetSize(), m_Config->GetServerIP().c_str(), m_Config->GetServerPort());
	}
}

void CDownloadFile::UpdateSources()
{
	// TODO
}

void CDownloadFile::SelectSocket()
{
	fd_set rSet;
	FD_ZERO(&rSet);
	FD_SET(m_Socket, &rSet);
	struct timeval t;
	t.tv_sec = 0;
	t.tv_usec = 100;

	if (select(m_Socket+1, &rSet, NULL, NULL, &t))
		RecvMessage();
}

void CDownloadFile::RecvMessage()
{
	unsigned char hexHash[16];
	MD52Hex(m_MD5.c_str(), hexHash);
	m_Protocol->Response(m_Socket, hexHash, &m_VecSource);	
}

bool CDownloadFile::InitSocket()
{
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	for (int i = m_Config->GetMinPort(); i <= m_Config->GetMaxPort(); ++i)
	{
		if (Bind(sock, NULL, i) == true)
		{
			m_Socket = sock;
			return true;
		}
	}
	return false;
}
