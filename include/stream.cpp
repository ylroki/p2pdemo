#include "stream.h"

CMemoryStream::CMemoryStream(void* buffer, Int64 size, Int64 maxSize)
	:m_Buffer(buffer),
	m_Size(size),
	m_MaxSize(maxSize),
	m_Pointer(0)
{}

CMemoryStream::~CMemoryStream()
{}

bool CMemoryStream::ReadBuffer(void* buffer, Int64 size)
{
	if (m_Pointer + size > m_Size)
		return false;
	memcpy(buffer, (char*)m_Buffer + m_Pointer, size);
	m_Pointer += size;
	return true;
}

bool CMemoryStream::WriteBuffer(const void* buffer, Int64 size)
{	
	if (m_Pointer + size > m_MaxSize)
		return false;
	memcpy((char*)m_Buffer + m_Pointer, buffer, size);
	m_Pointer += size;
	if (m_Pointer > m_Size)
		m_Size = m_Pointer;
	return true;
}

Int64 CMemoryStream::GetSize()
{
	return m_Size;
}

Int64 CMemoryStream::GetMaxSize()
{
	return m_MaxSize;
}
