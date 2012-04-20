#include "socket_header.h"

int main()
{
	const char* ip = "222.201.130.30";
	printf("%s\n", IPLong2String(IPString2Long(ip)).c_str());
	return 0;
}
