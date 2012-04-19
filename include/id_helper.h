#ifndef __INCLUDE_ID_HELPER_H__
#define __INCLUDE_ID_HELPER_H__
#include "auto_lock.h"
#include <string.h>
#define MAX_ID 1024 //from 0 to MAX_ID - 1
class CIDHelper
{
public:
	CIDHelper();
	~CIDHelper();
	short New();
	void Delete(short id);
	
private:
	bool m_Use[MAX_ID];
	CLock m_Lock;	
};
#endif
