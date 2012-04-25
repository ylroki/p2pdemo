#include "uint128.h"

CUInt128::CUInt128()
	:m_High(0),
	m_Low(0)
{}

CUInt128::~CUInt128()
{}

CUInt128 CUInt128::FromHex(const unsigned char* hex)
{
	CUInt128 ret;
	for (int i = 0; i < 8; ++i)
		ret.m_High = (ret.m_High<<8) + hex[i];
	for (int i = 8; i < 16; ++i)
		ret.m_Low = (ret.m_Low<<8) + hex[i];
	return ret;
}

CUInt128 CUInt128::FromMD5(const char* md5)
{
	unsigned char hex[16];
	MD52Hex(md5, hex);
	CUInt128 ret = FromHex(hex);
	return ret;
}

short CUInt128::FirstOneBit()
{
	for (short i = 63; i >=0; --i)
		if ((m_High&(1LL<<i)) != 0)
			return i + 64;
	for (short i = 63; i >=0; --i)
		if ((m_Low&(1LL<<i)) != 0)
			return i;
	return -1;	
}

CUInt128 CUInt128::XOR(const CUInt128& num)
{
	CUInt128 ret;
	ret.m_High = (this->m_High^num.m_High);
	ret.m_Low = (this->m_Low^num.m_Low);
	return ret;
}

void CUInt128::Print()
{
	printf("high:%llu low:%llu\n", m_High, m_Low);
}

CUInt128 CUInt128::FromInteger(UInt64 high, UInt64 low)
{
	CUInt128 ret;
	ret.m_High = high;
	ret.m_Low = low;
	return ret;
}

bool CUInt128::EqualTo(const CUInt128& other)
{
	if (m_High == other.m_High && m_Low == other.m_Low)
		return true;
	return false;
}

short CUInt128::GetBit(short bit)
{
	if (bit >= 0 && bit < 128)
	{
		if (bit >= 64)
		{
			bit -= 64;
			if ((m_High&(1LL<<bit)) == 0)
				return 0;
			else
				return 1;
		}
		else
		{
			if ((m_Low&(1LL<<bit)) == 0)
				return 0;
			else
				return 1;

		}
	}
	return -1;
}

void CUInt128::ToHex(unsigned char* hex)
{
	for (int i = 0; i < 8; ++i)
		hex[i] = ((m_High>>(56-i*8)) & 255LL);
	for (int i = 8; i < 16; ++i)
		hex[i] = ((m_Low>>(120-i*8)) & 255LL);
}

std::string CUInt128::ToMD5()
{
	unsigned char hex[16];
	this->ToHex(hex);
	return Hex2MD5String(hex);
}

bool operator==(const CUInt128& op1, const CUInt128& op2)
{
	if (op1.m_High == op2.m_High && op1.m_Low == op2.m_Low)
		return true;
	return false;
}

bool operator<(const CUInt128& op1, const CUInt128& op2)
{
	if (op1.m_High < op2.m_High ||
		(op1.m_High == op2.m_High && op1.m_Low < op2.m_Low))
		return true;
	return false;
}

bool operator>(const CUInt128& op1, const CUInt128& op2)
{
	return (op2 > op1);
}

bool operator<=(const CUInt128& op1, const CUInt128& op2)
{
	return (op1 < op2 || op1 == op2);
}

bool operator>=(const CUInt128& op1, const CUInt128& op2)
{
	return (op2 <= op1);
}

bool operator!=(const CUInt128& op1, const CUInt128& op2)
{
	return !(op1 == op2);
}

CUInt128 operator^(const CUInt128& op1, const CUInt128& op2)
{
	CUInt128 ret;
	ret.m_High = (op1.m_High ^ op2.m_High);
	ret.m_Low = (op1.m_Low ^ op2.m_Low);
	return ret;
}

CUInt128& CUInt128::operator=(const CUInt128& op)
{
	this->m_High = op.m_High;
	this->m_Low = op.m_Low;
	return *this;
}
