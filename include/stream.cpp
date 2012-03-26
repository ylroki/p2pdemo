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


CFileStream::CFileStream(const char* filename, int flag, mode_t mode)
	:m_File(FILE_ERROR),
	m_Pointer(0)
{
	if ((flag&O_CREAT) != 0)
		m_File = open(filename, flag, mode);	
	else
		m_File = open(filename, flag);
}

CFileStream::~CFileStream()
{
	if (m_File != FILE_ERROR)
		close(m_File);
}

Int64 CFileStream::Seek(Int64 offset, int whence)
{
	if (m_File != FILE_ERROR)
		return (m_Pointer = lseek(m_File, offset, whence));
	return -1;
}

Int64 CFileStream::Write(Int64 offset, const void* src, Int64 size)
{
	if (Seek(offset) != POINTER_ERROR)
		return Write(src, size);
	return -1;
}

Int64 CFileStream::Read(Int64 offset, void* dst, Int64 size)
{
	if (Seek(offset) != POINTER_ERROR)
		return Read(dst, size);
	return -1;
}

Int64 CFileStream::Write(const void* src, Int64 size)
{
	if (m_File != FILE_ERROR && m_Pointer != POINTER_ERROR)
	{
		m_Pointer += size;
		return write(m_File, src, size);
	}
	return -1;
}

Int64 CFileStream::Read(void* dst, Int64 size)
{
	if (m_File != FILE_ERROR && m_Pointer != POINTER_ERROR)
	{
		m_Pointer += size;
		return read(m_File, dst, size);
	}
}
