#ifndef __KAD_PROTOCOL_H__
#define __KAD_PROTOCOL_H__
#include "linux_header.h"
#include "socket_header.h"
#include "uint128.h"
class CKad;
class CMemoryStream;

class CKadProtocol
{
public:
	CKadProtocol(CKad* kad);
	~CKadProtocol();
	void RecvMessage(int sockfd = SOCKET_ERROR);

private:
	void FillNodesCloseTo(CUInt128 target, CMemoryStream* sender);
	CKad* m_Kad;
};

#endif
