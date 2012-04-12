#include "kad.h"

CKad::CKad(CConfig* config)
	:m_Config(config),
	m_Stopped(true),
	m_WorkThread(THREAD_ERROR),
	m_ListenThread(THREAD_ERROR),
	m_KeyLock(),
	m_Database(),
	m_RouteTable(NULL),
	m_ClientID()
{
	while (!m_QuePendingKeys.empty())
		m_QuePendingKeys.pop();
}

CKad::~CKad()
{}

bool CKad::Start()
{
	if (!m_Stopped)
		return true;
	m_Database.Open("cache/kad_keyvalue.db");
	m_Database.CreateTable("hash", "(md5 TEXT, ipv4 INTEGER, port INTEGER, primary key(md5,ipv4,port))");
	m_Database.CreateTable("filesize", "(md5 TEXT primary key, size INTEGER)");
	m_RouteTable = new CRouteTable();
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
	m_ClientID = CalculateClientID();
	JoinKad();
	while (!m_Stopped)
	{
		// TODO
		printf("work thread\n");
	}
	if (m_ListenThread != THREAD_ERROR)
		pthread_join(m_ListenThread, NULL);
	printf("stop working\n");
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
		Sleep(1);
	}
	printf("stop listening\n");
}

void CKad::JoinKad()
{
	m_RouteTable->SetClientID(m_ClientID);
	m_RouteTable->InitTable("config/kad_init_node.conf");
	// TODO: Find its own node id.
}

void CKad::FindSource(const unsigned char* key, unsigned long* filesize, std::vector<TPeer>* source)
{
	// TODO: Try to find key in local db.
	std::string md5 = Hex2MD5String(key);
	*filesize = GetFileSize(m_Database, md5.c_str());
	char sql[BUF_SIZE];
	sprintf(sql, "select ipv4,port from hash where md5='%s'", md5.c_str());
	m_Database.Execute(sql, DealEachSource, source);
	if (source->size())
		return;

	// Failed to find key in local db, should lock.
	CAutoLock lock(&m_KeyLock);
	m_QuePendingKeys.push(md5);
}

unsigned long CKad::GetFileSize(CDatabase database, const char* md5)
{
	char sql[BUF_SIZE];
	sprintf(sql, "select size from filesize where md5='%s'", md5);
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

CUInt128 CKad::CalculateClientID()
{
	CUInt128 id;
	return id;
}

bool CKad::Ping(const TNode& node)
{
	return true;
}
