#ifndef __INCLUDE_STREAM_H__
#define __INCLUDE_STREAM_H__

#include "linux_header.h"

class CMemoryStream
{
public:
	CMemoryStream(void* buffer, Int64 size);
	~CMemoryStream();
	bool ReadBuffer(void* buffer, Int64 size);
	bool WriteBuffer(const void* buffer, Int64 size);
	Int64 GetSize();

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
	Int64 m_Pointer;

};

#endif
