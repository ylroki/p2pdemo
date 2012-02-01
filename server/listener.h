#ifndef __SERVER_LISTENER_H__
#define __SERVER_LISTENER_H__

#include <pthread.h>
class CListener
{
public:
	bool Start();
	void Stop();
	CListener();
	~CListener();

private:	
	static void* ThreadFunc(void* arg);
	void ListenThread();
	bool m_IsStopped;
	pthread_t m_Thread;
};


#endif
