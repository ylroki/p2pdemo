#ifndef __INCLUDE_STREAM_H__
#define __INCLUDE_STREAM_H__

#include "linux_header.h"

class CMemoryStream
{
public:
	CMemoryStream(void* buffer, Int64 size = 0, Int64 maxSize = BUF_SIZE);
	~CMemoryStream();
	bool ReadBuffer(void* buffer, Int64 size);
	bool WriteBuffer(const void* buffer, Int64 size);
	Int64 GetSize();
	Int64 GetMaxSize();

	template <typename Integer>
	inline Integer ReadInteger()
	{
		Integer i;
		ReadBuffer(&i, sizeof(i));
		return i;
	}

	template <typename Integer>
	inline bool WriteInteger(Integer i)
	{
		return WriteBuffer(&i, sizeof(i));
	}

private:
	void* m_Buffer;
	Int64 m_Size;
	Int64 m_MaxSize;
	Int64 m_Pointer;

};


#define FILE_ERROR -1
#define POINTER_ERROR -1
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
class CFileStream
{
public:
	CFileStream(const char* filename, int flag, mode_t mode = FILE_MODE);
	~CFileStream();
	Int64 Seek(Int64 offset, int whence = SEEK_SET);
	Int64 Write(Int64 offset, const void* src, Int64 size);
	Int64 Read(Int64 offset, void* dst, Int64 size);
	Int64 Write(const void* src, Int64 size);
	Int64 Read(void* dst, Int64 size);

	template <typename Integer>
	inline Integer ReadInteger(Int64 offset)
	{
		Integer i;
		Read(offset, &i, sizeof(i));
		return i;
	}

	template <typename Integer>
	inline Int64 WriteInteger(Int64 offset, Integer i)
	{
		return Write(offset, &i, sizeof(i));
	}
private:
	int m_File;
	Int64 m_Pointer;
};

#endif

