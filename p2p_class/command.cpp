#include "command.h"
// Client foreground process send to Client background process.
const char* g_LocalCommand[] = {"stop", "download"};

bool IsLocalCommand(const char* command)
{
	int size = sizeof(g_LocalCommand) / sizeof(char*);
	for (int i = 0; i < size; ++i)
		if (strcmp(command, g_LocalCommand[i]) == 0)
			return true;
	return false;
}


