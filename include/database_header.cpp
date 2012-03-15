#include "database_header.h"

CDatabase::CDatabase()
	:m_DB(NULL)
{
}

CDatabase::~CDatabase()
{}

bool CDatabase::Open(const char* filename)
{
	if (m_DB)
		return false;
	int ret = sqlite3_open(filename, &m_DB);
	if (ret)
	{
		sqlite3_close(m_DB);
		return false;
	}
	return true;
}

void CDatabase::Close()
{
	if (m_DB)
		sqlite3_close(m_DB);
}
