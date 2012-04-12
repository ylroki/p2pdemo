#include "uint128.h"

int main()
{
	char md5[] = "00000000000000010000000000000000";
	unsigned char hex[16];
	MD52Hex(md5, hex);
	CUInt128 a = CUInt128::FromMD5(md5);
	a.Print();
	CUInt128 b = CUInt128::FromHex(hex);
	b.Print();
	printf("%hu\n", a.FirstOneBit());
	CUInt128 c = CUInt128::FromInteger(0, 1);
	c.Print();
	printf("%hu\n", c.FirstOneBit());
	return 0;
}
