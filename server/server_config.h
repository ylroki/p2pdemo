#ifndef __SERVER_CONFIG_H__
#define __SERVER_CONFIG_H__
#include "linux_header.h"
#include "string_header.h"

class CConfig
{
public:
	CConfig();
	~CConfig();
	bool Init(const char* filename);
	int GetPort();

private:
	int m_Port;
};

#endif
