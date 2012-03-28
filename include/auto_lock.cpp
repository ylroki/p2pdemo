#include "auto_lock.h"

CLock::CLock()
{
	pthread_mutex_init(&m_Mutex, NULL);
}

CLock::~CLock()
{
	pthread_mutex_destroy(&m_Mutex);
}

void CLock::Lock()
{
	pthread_mutex_lock(&m_Mutex);
}

void CLock::Unlock()
{
	pthread_mutex_unlock(&m_Mutex);
}

CAutoLock::CAutoLock(CLock* lock)
	:m_Lock(lock)
{
	if (m_Lock)
		m_Lock->Lock();
}

CAutoLock::~CAutoLock()
{
	if (m_Lock)
		m_Lock->Unlock();
}
