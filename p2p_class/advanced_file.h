#ifndef __P2P_CLASS_ADVANCED_FILE_H__
#define __P2P_CLASS_ADVANCED_FILE_H__
#include "stream.h"
#define BLOCK_SIZE 1024
class CAdvancedFile
{
public: 
	CAdvancedFile(const char* filename, Int64 size);
	~CAdvancedFile();
	Int64 FirstBlock();
	Int64 Write(Int64 offset, const void* src, Int64 size);
	Int64 Read(Int64 offset, void* dst, Int64 size);
	void PrintBlock();
	char GetPercent();
	Int64 GetBlockOk();

private:
	void InitBlockFile();
	void SetBlock(Int64 offset);

	std::string m_Filename;
	std::string m_BlockFilename;
	CFileStream* m_FileStream;
	CFileStream* m_BlockStream;
	Int64 m_Size;
	Int64 m_BlockNum;
	Int64 m_BlockOk;
};

#endif
