#include "advanced_file.h"

const char* str = "1234567890";
int main()
{
	CAdvancedFile file("test.txt", BLOCK_SIZE+10);
	printf("\n-------------------------------\n");

	Int64 n;
	while ((n = file.FirstBlock()) != -1)
	{
		file.PrintBlock();
		printf("\n");
		file.Write(n, str, 10);
		printf("\n-------------------------------\n");
	}
	return 0;
}
