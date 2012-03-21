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

bool CDatabase::Open(const std::string filename)
{
	return Open(filename.c_str());
}

void CDatabase::Close()
{
	if (m_DB)
		sqlite3_close(m_DB);
}

bool CDatabase::Execute(const char* sql, ExecuteCallback func, void* arg)
{
	if (m_DB)
	{
		int ret = sqlite3_exec(m_DB, sql, func, arg, NULL);
		return (ret == SQLITE_OK);
	}
	return false;
}

bool CDatabase::GetTable(const char* sql, char*** result, int* nRow, int* nCol)
{
	if (m_DB)
	{
		int ret = sqlite3_get_table(m_DB, sql, result, nRow, nCol, NULL);
		return (ret == SQLITE_OK);
	}
	return false;
}

bool CDatabase::CreateTable(const char* tbName, const char* colDef)
{
	char sql[BUF_SIZE];
	sprintf(sql, "create table if not exists %s%s", tbName, colDef);
	return Execute(sql);
}
