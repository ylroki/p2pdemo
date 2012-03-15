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
	void Close();

private:
	sqlite3* m_DB;
};

#endif
