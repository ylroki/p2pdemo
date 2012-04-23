#ifndef __KAD_PROTOCOL_H__
#define __KAD_PROTOCOL_H__
#include "linux_header.h"
#include "socket_header.h"
class CKad;

class CKadProtocol
{
public:
	CKadProtocol(CKad* kad);
	~CKadProtocol();
	void RecvMessage(int sockfd = SOCKET_ERROR);

private:
	CKad* m_Kad;
};

#endif
