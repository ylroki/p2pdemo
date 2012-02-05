#ifndef __CLIENT_SOURCE_H__
#define __CLIENT_SOURCE_H__

class CSource
{
public:
	CSource(std::string ip, int port);
	~CSource();
	bool Start();
	void Stop();
	void RequestBlock();

private:
	static void* ThreadFunc(void* arg);
	void Work();
	std::string m_IPv4;
	int m_Port;

};

#endif
