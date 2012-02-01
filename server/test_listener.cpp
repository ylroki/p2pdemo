#include <stdio.h>
#include <unistd.h>
#include "listener.h"

int main()
{
	CListener ltner;
	if (ltner.Start())
	{
		printf("Start ok\n");
		sleep(10);
		ltner.Stop();
		printf("Stop ok\n");
	}
	else
	{
		printf("Oh no\n");
	}
	return 0;
}
