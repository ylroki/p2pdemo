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

void CDatabase::Execute(const char* sql)
{
	if (m_DB)
		sqlite3_exec(m_DB, sql, NULL, NULL, NULL);
}

void CDatabase::GetTable(const char* sql, char*** result, int* nRow, int* nCol)
{
	if (m_DB)
		sqlite3_get_table(m_DB, sql, result, nRow, nCol, NULL);
}
