#ifndef __INCLUDE_AUTO_LOCK_H__
#define __INCLUDE_AUTO_LOCK_H__
#include <pthread.h>
class CLock
{
public:
	CLock();
	~CLock();
	Lock();
	Unlock();

private:
	pthread_mutex_t m_Mutex;
};

class CAutoLock
{
public:
	CAutoLock(CLock* lock);
	~CAutoLock();
private:
	CLock* m_Lock;
};
#endif
