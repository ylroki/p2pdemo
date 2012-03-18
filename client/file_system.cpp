#include "file_system.h"

CFileSystem::CFileSystem()
	:m_Thread(THREAD_ERROR),
	m_Stopped(true),
	m_Config(NULL),
	m_PastTime(0)
{
}

CFileSystem::~CFileSystem()
{}

bool CFileSystem::Start(CConfig* config)
{
	if (!m_Stopped)
		return true;
	m_Config = config;
	if (m_Database.Open(m_Config->GetCacheDir()+"/hash.db") == false)
		return false;
	if (m_Database.CreateTable("hash", "(md5 TEXT primary key, path TEXT)") == false)
		return false;

	m_Stopped = false;
	if (0 == pthread_create(&m_Thread, NULL, ThreadFunc, this))
		return true;
	m_Stopped = true;
	return false;
}

void CFileSystem::Stop()
{
	m_Stopped = true;
	if (m_Thread != THREAD_ERROR)
		pthread_join(m_Thread, NULL);
	m_Database.Close();
}

void* CFileSystem::ThreadFunc(void* arg)
{
	CFileSystem* fs = static_cast<CFileSystem*>(arg);
	fs->Work();
	return ((void*)0);
}

void CFileSystem::Work()
{
	while (!m_Stopped)
	{
		if (m_PastTime == 0 || m_PastTime / 60000 >= m_Config->GetUpdatePeriod())
		{
			m_PastTime = 0;
			FindResources();
		}
		Sleep(100);
		m_PastTime += 100;
	}
}

void CFileSystem::FindResources()
{
	std::queue<std::string> queFile;
	queFile.push(m_Config->GetDirectory());
	while (!queFile.empty())
	{
		std::string file = queFile.front();
		queFile.pop();
		struct stat statbuf;
		if (lstat(file.c_str(), &statbuf) == -1)
		{
			perror(file.c_str());
			continue;
		}
		if (S_ISDIR(statbuf.st_mode) == 0)// not a directory
		{
			DealFile(file);
		}
		else
		{
			struct dirent* dirp;
			DIR* dp;
			if ((dp = opendir(file.c_str())) == NULL)
				continue;
			if (file[file.size() - 1] != '/')
				file.append("/");
			while ((dirp = readdir(dp)) != NULL)
			{
				if (strcmp(dirp->d_name, ".") == 0 ||
					strcmp(dirp->d_name, "..") == 0)
					continue;
				std::string chFile = file + dirp->d_name;
				queFile.push(chFile);
			}
		}

	}
}

void CFileSystem::DealFile(const std::string file)
{
	unsigned char hexHash[16];
	MD5File(file.c_str(), hexHash);
	char md5[33];
	md5[32] = 0;
	Hex2MD5(hexHash, md5);
	printf("a file %s %s\n", file.c_str(), md5);
	char sql[BUF_SIZE];
	sprintf(sql, "insert into hash values('%s', '%s')", 
				md5, file.c_str());
	m_Database.Execute(sql);
}
