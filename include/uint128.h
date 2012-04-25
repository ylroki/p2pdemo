#ifndef __INCLUDE_UINT128_H__
#define __INCLUDE_UINT128_H__
#include "linux_header.h"
#include "md5_header.h"
class CUInt128
{
public:
	CUInt128();
	~CUInt128();
	short FirstOneBit();
	CUInt128 XOR(const CUInt128& num);
	short GetBit(short bit);
	static CUInt128 FromMD5(const char* md5);
	static CUInt128 FromInteger(UInt64 high, UInt64 low);
	static CUInt128 FromHex(const unsigned char* hex);
	bool EqualTo(const CUInt128& other);
	void Print();
	void ToHex(unsigned char* hex);
	std::string ToMD5();
	CUInt128& operator=(const CUInt128& op);
	friend bool operator==(const CUInt128& op1, const CUInt128& op2);
	friend bool operator<(const CUInt128& op1, const CUInt128& op2);
	friend bool operator>(const CUInt128& op1, const CUInt128& op2);
	friend bool operator<=(const CUInt128& op1, const CUInt128& op2);
	friend bool operator>=(const CUInt128& op1, const CUInt128& op2);
	friend bool operator!=(const CUInt128& op1, const CUInt128& op2);
	friend CUInt128 operator^(const CUInt128& op1, const CUInt128& op2);

private:
	UInt64 m_High;
	UInt64 m_Low;
};

#endif
