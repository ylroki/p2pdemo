#include "download_file.h"
#include "kad.h"
#include "protocol_manager.h"

CDownloadFile::CDownloadFile(const char* md5)
	:m_Status(DS_WAIT),
	m_Thread(THREAD_ERROR),
	m_Socket(SOCKET_ERROR),
	m_Config(NULL),
	m_MD5(md5),
	m_Protocol(NULL),
	m_AdFile(NULL),
	m_Kad(NULL),
	m_Speed(0),
	m_Clock(0),
	m_StartTime(0),
	m_PastTime(0),
	m_LastSecBlock(0)
{
	m_VecSource.clear();	
	m_WorkSource.clear();
	m_Ticker.clear();
	m_Session.clear();
}

CDownloadFile::~CDownloadFile()
{
	m_VecSource.clear();	
	m_WorkSource.clear();
}

KDownStatus CDownloadFile::GetStatus()
{
	return m_Status;
}

bool CDownloadFile::Start(CConfig* config)
{
	if (m_Status == DS_RUNNING)
		return true;
	m_StartTime = GetNowSeconds();
	m_Config = config;
	m_Protocol = new CProtocolManager(config);
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
	if (m_Socket != SOCKET_ERROR)
		close(m_Socket);
	if (m_AdFile)
		delete m_AdFile;
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
		time_t now = GetNowSeconds();
		m_PastTime = now - m_StartTime;
		if (now - m_Clock >= 1)
		{
			if (m_AdFile)
			{
				m_Speed = m_AdFile->GetBlockOk() - m_LastSecBlock;
				m_LastSecBlock += m_Speed;
			}
			m_Clock = now;
		}
		RequestSources();
		UpdateSources();
		SelectSocket();
		Sleep(1);
	}
}
const int g_LowerBoundOfSources = 1;
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

		//kad
		static time_t kadTime = 0;
		if (m_Kad)
		{
			std::vector<TPeer> source;
			unsigned long filesize;
			unsigned char key[16];
			MD52Hex(m_MD5.c_str(), key);
			bool flag = false;
			time_t now = GetNowSeconds();
			if (now - kadTime > 10)
			{
				kadTime = now;
				flag = true;
			}
			if (m_Kad->FindSource(key, &filesize, &source, flag) == true)
				DealSourceResponse(key, filesize, &source);
		}
	}
}
const int g_NWork = 1;
void CDownloadFile::UpdateSources()
{
	if (g_NWork > m_WorkSource.size())
	{
		for (size_t i = 0; i < m_VecSource.size(); ++i)		
		{
			TPeer peer = m_VecSource[i];
			time_t now = GetNowSeconds();
			std::map<unsigned long, time_t>::iterator it = m_Session.find(peer.SessionID);
			if (it != m_Session.end())
			{
				if (now - it->second <= 1)
					continue;
			}
			m_Session[peer.SessionID] = now;
			m_Protocol->SendCommand(0x21, m_Socket, m_MD5.c_str(), &peer);
		}
	}

	// TEST: just use a source
	if (m_WorkSource.size() >= 1)
	{
		TPeer peer = m_WorkSource.front();
		RequestFileData(peer);
		m_WorkSource.pop_front();
		m_WorkSource.push_back(peer);
	}
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
	m_Protocol->Response(m_Socket, this);	
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

void CDownloadFile::DealSourceResponse(const unsigned char* hexHash, unsigned long filesize, 
	std::vector<TPeer>* vecSource)
{
	if (MD5IsSame2Hex(m_MD5.c_str(), hexHash) == false)
		return ;
	if (m_AdFile == NULL)
		m_AdFile = new CAdvancedFile(m_MD5.c_str(), filesize);
	for (size_t i = 0; i < vecSource->size(); ++i)
		m_VecSource.push_back((*vecSource)[i]);	
}

void CDownloadFile::DealCheckResult(const unsigned char* hexHash, unsigned long sessionID, char status)
{
	if (MD5IsSame2Hex(m_MD5.c_str(), hexHash) == false)
		return ;
	for (size_t i = 0; i < m_VecSource.size(); ++i)
	{
		if (m_VecSource[i].SessionID == sessionID)
		{
			if (status)
				m_WorkSource.push_back(m_VecSource[i]);
			m_VecSource[i] = m_VecSource[m_VecSource.size() - 1];
			m_VecSource.pop_back();
			break;
		}
	}
	std::map<unsigned long, time_t>::iterator it = m_Session.find(sessionID);
	if (it != m_Session.end())
		m_Session.erase(it);
}

void CDownloadFile::RequestFileData(TPeer peer)
{
	unsigned long offset = m_AdFile->FirstBlock();
	if (offset == -1)
	{
		m_Status = DS_DONE; 
		printf("File done.\n");
		return;
	}

	time_t now = GetNowSeconds();
	std::map<unsigned long, time_t>::iterator it = m_Ticker.find(offset);
	if (it != m_Ticker.end())
	{
		if (now - it->second <= 1)
			return;
	}
	m_Ticker[offset] = now;
	m_Protocol->SendCommand(0x22, m_Socket, &peer, m_MD5.c_str(), offset, offset+7);
}

void CDownloadFile::DealFileData(const unsigned char* hexHash,
	unsigned long offset, const char* src, unsigned long size)
{
	if (MD5IsSame2Hex(m_MD5.c_str(), hexHash) == false)
		return ;
	if (m_AdFile)
		m_AdFile->Write(offset, src, size);
	std::map<unsigned long, time_t>::iterator it = m_Ticker.find(offset);
	if (it != m_Ticker.end())
		m_Ticker.erase(it);
}

void CDownloadFile::SetKad(CKad* kad)
{
	m_Kad = kad;
}

void CDownloadFile::GetDetail(KDownStatus& status, char& percent, std::string& md5, 
	time_t& past, unsigned short& speed)
{
	status = m_Status;
	if (m_AdFile)
		percent = m_AdFile->GetPercent();
	else
		percent = 0;
	md5 = m_MD5;
	past = m_PastTime;
	speed = m_Speed;
}
