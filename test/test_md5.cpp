#include "md5_header.h"
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
			unsigned char hash[16];
			MD5File(argv[2], hash);
			for (int i = 0; i < 16; ++i)
				printf("%02x", hash[i]);
			printf("\n");

			char md5[33];
			md5[32] = 0;
			Hex2MD5(hash, md5);
			MD52Hex(md5, hash);
			Hex2MD5(hash, md5);
			printf("%s\n", md5);
		}
	}
	return 0;
}

