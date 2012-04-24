#include "uint128.h"
#include "md5_header.h"

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

	char md5_2[] = "000102030405060708090a0b0c0d0e0f";
	CUInt128 x = CUInt128::FromMD5(md5_2);
	x.Print();
	x.ToHex(hex);
	printf("%s\n", Hex2MD5String(hex).c_str());

	CUInt128 y = CUInt128::FromInteger(1LL, 1LL);
	CUInt128 z = CUInt128::FromInteger(1LL, 0LL);
	printf("y == z:%d\n",y==z);
	printf("y == y:%d\n",y==y);
	printf("y < z:%d\n",y<z);
	printf("z < y:%d\n",z<y);
	return 0;
}
