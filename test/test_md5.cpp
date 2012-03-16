#include "linux_header.h"
#include <openssl/md5.h>

int main(int argc, char* argv[])
{
	if (argc > 2)
	{
		if (strcmp(argv[1], "-s") == 0)
		{
			unsigned char str[BUF_SIZE];
			int len = strlen(argv[2]);
			for (int i = 0; i < len; ++i)
				str[i] = argv[2][i];
			unsigned char buf[16];
			MD5(str, len, buf);
			for (int i = 0; i < 16; ++i)
				printf("%02x", buf[i]);
			printf("\n");
		}
		else if (strcmp(argv[1], "-f") == 0)
		{
			int fd = open(argv[2], O_RDWR);
			if (fd != -1)
			{
				MD5_CTX md;
				unsigned char buf[BUF_SIZE];
				int n;
				MD5_Init(&md);
				while ((n = read(fd, buf, BUF_SIZE)) > 0)
				{
					MD5_Update(&md, buf, n);
				}
				unsigned char hash[16];
				MD5_Final(hash, &md);
				for (int i = 0; i < 16; ++i)
					printf("%02x", hash[i]);
				printf("\n");

			}
		}
	}
	return 0;
}

