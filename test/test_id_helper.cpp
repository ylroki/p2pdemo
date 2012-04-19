#include "stdio.h"
#include "id_helper.h"

int main()
{
	CIDHelper help;
	for (int i = 0; i < 5; ++i)
		printf("%hd\n", help.New());
	help.Delete(3);
	printf("%hd\n", help.New());

	return 0;
}
