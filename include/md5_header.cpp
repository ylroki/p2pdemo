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
