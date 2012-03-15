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
	printf("a file %s\n", file.c_str());
}
