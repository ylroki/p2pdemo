#include "config.h"

CConfig::CConfig()
	:m_Port(8000)
{
}

CConfig::~CConfig()
{
}

bool CConfig::Init(const char* filename)
{
	FILE* file = fopen(filename, "r");
	if (file == NULL)
		return false;

	char buf[BUF_SIZE];
	if (fgets(buf, BUF_SIZE, file) == NULL)
		return false;
	
	if (fgets(buf, BUF_SIZE, file) == NULL)
		return false;
	m_Port = atoi(buf);
	
	fclose(file);
	return true;
}

int CConfig::GetPort()
{
	return m_Port;
}
