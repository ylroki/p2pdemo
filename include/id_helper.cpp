#include "id_helper.h"

CIDHelper::CIDHelper()
{
	memset(m_Use, 0, sizeof(m_Use));
}

CIDHelper::~CIDHelper()
{}

short CIDHelper::New()
{
	CAutoLock lock(&m_Lock);
	for (short i = 0; i < MAX_ID; ++i)
		if (m_Use[i] == false)
		{
			m_Use[i] = true;
			return i;
		}
}

void CIDHelper::Delete(short id)
{
	CAutoLock lock(&m_Lock);
	if (id >=0 && id < MAX_ID)	
		m_Use[id] = false;
}
