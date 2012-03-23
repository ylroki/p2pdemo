#include "md5_header.h"

bool MD5File(const char* filename, unsigned char* hexHash)
{
	int fd = open(filename, O_RDONLY);
	if (fd == -1)
		return false;
	MD5_CTX ctx;
	MD5_Init(&ctx);
	unsigned char buf[BUF_SIZE];
	int n;
	while ((n = read(fd, buf, BUF_SIZE)) > 0)
	{
		MD5_Update(&ctx, buf, n);
	}
	MD5_Final(hexHash, &ctx);
	return true;
}

bool MD5File(const std::string filename, unsigned char* hexHash)
{
	return MD5File(filename.c_str(), hexHash);
}

int Char2Hex(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (ch - '0');
	if (ch >= 'a' && ch <= 'f')
		return (ch - 'a' + 10);
	return -1;
}

char Hex2Char(int hex)
{
	if (hex >= 0 && hex <= 9)
		return hex + '0';
	if (hex >= 10 && hex <= 15)
		return hex - 10 + 'a';
	return 0;
}

void MD52Hex(const char* md5, unsigned char* hex)
{
	for (int i = 0; i < 32; i+=2)
	{	
		hex[i/2] = Char2Hex(md5[i])*16 + Char2Hex(md5[i+1]);
	}
}

void Hex2MD5(const unsigned char* hex, char* md5)
{
	for (int i = 0; i < 16; ++i)
	{
		md5[i*2] = Hex2Char((hex[i]>>4));
		md5[i*2+1] = Hex2Char((hex[i]&0x0f));
	}
}

bool MD5IsSame2Hex(const char* md5, const unsigned char* hexHash)
{
	unsigned char hash[16];
	MD52Hex(md5, hash);
	if (memcmp(hash, hexHash, 16))
		return false;
	return true;
}
