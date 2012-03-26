#include "advanced_file.h"

CAdvancedFile::CAdvancedFile(const char* filename, Int64 size)
	:m_Filename(filename),
	m_FileStream(NULL),
	m_BlockStream(NULL),
	m_Size(size)
{
	m_BlockNum = m_Size / BLOCK_SIZE;
	if (m_Size % BLOCK_SIZE)
		++m_BlockNum;
	m_BlockFilename = m_Filename + ".cfg";
	bool fok = (access(filename, F_OK) == 0);
	bool bok = (access(m_BlockFilename.c_str(), F_OK) == 0);
	
	if (fok && bok)
	{
		m_FileStream = new CFileStream(m_Filename.c_str(), O_RDWR);
		m_BlockStream = new CFileStream(m_BlockFilename.c_str(), O_RDWR);
	}
	else
	{
		m_FileStream = new CFileStream(m_Filename.c_str(), O_RDWR|O_CREAT|O_TRUNC);
		m_BlockStream = new CFileStream(m_BlockFilename.c_str(), O_RDWR|O_CREAT|O_TRUNC);
		InitBlockFile();
	}
}

CAdvancedFile::~CAdvancedFile()
{
	if (m_FileStream)
		delete m_FileStream;
	if (m_BlockStream)
		delete m_BlockStream;
}

Int64 CAdvancedFile::FirstBlock()
{
	char buf[BUF_SIZE];
	int n = 0;
	Int64 ret = 0;
	while ((n = m_BlockStream->Read(ret, buf, BUF_SIZE)) > 0)
	{
		for (int i = 0; i < n; ++i)
			if (buf[i] == 0)
				return (ret + i);
		ret += n;
	}
	return -1;
}

void CAdvancedFile::InitBlockFile()
{
	for (Int64 i = 0; i < m_BlockNum; ++i)
		m_BlockStream->WriteInteger<char>(i, 0);
}

Int64 CAdvancedFile::Write(Int64 offset, const void* src, Int64 size)
{
	Int64 ret = m_FileStream->Write(offset*BLOCK_SIZE, src, size);
	SetBlock(offset);
	return ret;
}

void CAdvancedFile::SetBlock(Int64 offset)
{
	m_BlockStream->WriteInteger<char>(offset, 0x01);
}

Int64 CAdvancedFile::Read(Int64 offset, void* dst, Int64 size)
{
	return m_FileStream->Read(offset*BLOCK_SIZE, dst, size);
}

void CAdvancedFile::PrintBlock()
{
	for (Int64 i = 0; i < m_BlockNum; ++i)
	{
		char buf;
		m_BlockStream->Read(i, &buf, 1);
		printf("%02x", buf);
	}
}
