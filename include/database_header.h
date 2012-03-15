#ifndef __INCLUDE_DATABASE_HEADER_H__
#define __INCLUDE_DATABASE_HEADER_H__

#include <sqlite3.h>

class CDatabase
{
public:
	CDatabase();
	~CDatabase();
	bool Open(const char* filename);
	void Close();

private:
	sqlite3* m_DB;
};

#endif
