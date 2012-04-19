#include "kad.h"

CKad::CKad(CConfig* config, CFileSystem* filesystem)
	:m_Config(config),
	m_FileSystem(filesystem),
	m_Stopped(true),
	m_WorkThread(THREAD_ERROR),
	m_ListenThread(THREAD_ERROR),
	m_KeyLock(),
	m_Database(),
	m_RouteTable(NULL),
	m_ClientID(),
	m_LastRepublish(0),
	m_LastRefresh(0),
	m_TaskManager(NULL)
{
	m_TaskManager = new CTaskManager();
}

CKad::~CKad()
{
	if (m_TaskManager)
		delete m_TaskManager;
}

bool CKad::Start()
{
	if (!m_Stopped)
		return true;
	m_Database.Open("cache/kad_keyvalue.db");
	m_Database.CreateTable("hash", "(md5 TEXT, ipv4 INTEGER, port INTEGER, size INTEGER,\
		primary key(md5,ipv4,port))");
	m_ClientID = CalculateClientID();
	m_RouteTable = new CRouteTable(NULL, m_ClientID, 0, true);
	m_Stopped = false;
	if (0 == pthread_create(&m_WorkThread, NULL, WorkThread, this))
		return true;
	m_Stopped = true;
	return false;
}

void CKad::Stop()
{
	m_Stopped = true;
	if (m_WorkThread != THREAD_ERROR)
		pthread_join(m_WorkThread, NULL);
	if (m_RouteTable)
		delete m_RouteTable;
	m_Database.Close();
}

void* CKad::WorkThread(void* arg)
{
	CKad* kad = static_cast<CKad*>(arg);
	kad->Work();
	return ((void*)0);
}

void CKad::Work()
{
	if (pthread_create(&m_ListenThread, NULL, ListenThread, this))
		return;
	JoinKad();
	while (!m_Stopped)
	{
		struct timeval tv;
		gettimeofday(&tv, NULL);
		time_t nowSec = tv.tv_sec;
		if (nowSec > m_LastRefresh && nowSec - m_LastRefresh > KAD_PERIOD_REFRESH*3600)
		{
			Refresh();
			m_LastRefresh = nowSec;
		}
		if (nowSec > m_LastRepublish && nowSec - m_LastRepublish > KAD_PERIOD_REPUBLISH*3600)
		{
			Republish();
			m_LastRepublish = nowSec;
		}
		m_TaskManager->Update();
		Sleep(100);
	}
	if (m_ListenThread != THREAD_ERROR)
		pthread_join(m_ListenThread, NULL);
}

void* CKad::ListenThread(void* arg)
{
	CKad* kad = static_cast<CKad*>(arg);
	kad->Listen();
	return ((void*)0);
}

void CKad::Listen()
{
	while (!m_Stopped)
	{
		// TODO
		printf("listen thread\n");
		Sleep(100);
	}
	printf("stop listening\n");
}

void CKad::JoinKad()
{
	m_RouteTable->InitTable("config/kad_init_node.conf");
	CTask* task = new CTaskFindNode(m_ClientID);
	m_TaskManager->Add(task);
}

void CKad::FindSource(const unsigned char* key, unsigned long* filesize, std::vector<TPeer>* source)
{
	std::string md5 = Hex2MD5String(key);
	*filesize = GetFileSize(m_Database, md5.c_str());
	char sql[BUF_SIZE];
	sprintf(sql, "select ipv4,port from hash where md5='%s'", md5.c_str());
	m_Database.Execute(sql, DealEachSource, source);
	if (source->size())
		return;

	// Failed to find key in local db, should lock.
	CAutoLock lock(&m_KeyLock);
	CTask* task = new CTaskFindValue(CUInt128::FromMD5(md5.c_str()));
	m_TaskManager->Add(task);
}

unsigned long CKad::GetFileSize(CDatabase database, const char* md5)
{
	char sql[BUF_SIZE];
	sprintf(sql, "select size from hash where md5='%s'", md5);
	char** res;
	int nRow = 0;
	int nCol = 0;
	database.GetTable(sql, &res, &nRow, &nCol);
	if (nRow >= 1)
		return atoi(res[nCol]);
	else
		return 0;
}


int CKad::DealEachSource(void* arg, int nCol, char** result, char** name)
{
	std::vector<TPeer>* source = static_cast<std::vector<TPeer>*>(arg);
	TPeer peer;
	peer.IPv4 = atoi(result[0]);
	peer.Port = atoi(result[1]);
	source->push_back(peer);
	return 0;
}

int CKad::RepublishHelper(void* arg, int nCol, char** result, char** name)
{
	CTaskManager* manager = static_cast<CTaskManager*>(arg);
	std::string md5 = result[0];
	unsigned long ip = atoi(result[1]);
	unsigned short port = atoi(result[2]);
	CTask* task = new CTaskSimpleStore(md5, ip, port);
	manager->Add(task);
	return 0;
}

CUInt128 CKad::CalculateClientID()
{
	CUInt128 id = CUInt128::FromInteger(IPString2Long(m_Config->GetPeerIP().c_str()), 
		m_Config->GetKadPort());
	return id;
}

void CKad::Republish()
{
	printf("republish\n");
	UpdateSelfKey();
	char sql[BUF_SIZE];
	sprintf(sql, "select * from hash");
	m_Database.Execute(sql, RepublishHelper, m_TaskManager);
}

void CKad::Refresh()
{
	printf("refresh\n");
	std::list<TNode> nodes;
	m_RouteTable->GetAll(&nodes);
	std::list<TNode>::iterator it;
	for (it = nodes.begin(); it != nodes.end(); ++it)
	{
		CTask* task = new CTaskPing(*it);
		task->SetTimeout(3000);
		m_TaskManager->Add(task);
	}
}

void CKad::UpdateSelfKey()
{
	unsigned long ip = IPString2Long(m_Config->GetPeerIP().c_str());
	unsigned short port = m_Config->GetKadPort();
	std::map<std::string, unsigned long>keys;
	m_FileSystem->GetAllHashes(&keys);
	std::map<std::string, unsigned long>::iterator it;
	for (it = keys.begin(); it != keys.end(); ++it)
	{
		std::string md5 = it->first;
		unsigned long size = it->second;
		char sql[BUF_SIZE];
		sprintf(sql, "insert into hash values('%s', %lu, %hu, %lu)",
			md5.c_str(), ip, port, size);
		m_Database.Execute(sql);
	}
}
