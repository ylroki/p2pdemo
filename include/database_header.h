#ifndef __INCLUDE_DATABASE_HEADER_H__
#define __INCLUDE_DATABASE_HEADER_H__

#include "linux_header.h"
#include <sqlite3.h>

class CDatabase
{
public:
	CDatabase();
	~CDatabase();
	bool Open(const char* filename);
	bool Open(const std::string);
	bool Execute(const char* sql);
	bool GetTable(const char* sql, char*** result, int* nRow, int* nCol);
	bool CreateTable(const char* tbName, const char* colDef);
	void Close();

private:
	sqlite3* m_DB;
};

#endif
