#ifndef __INCLUDE_COMMAND_H__
#define __INCLUDE_COMMAND_H__
#include <linux_header.h>

// Client foreground process send to Client background process.
extern const char* g_LocalCommand[];

bool IsLocalCommand(const char* command);

enum KC2SCommand
{};

enum KP2PCommand
{
	PPC_CHECK = 0x21,
	PPC_CHECK_RESULT = 0x31,
	PPC_GET_FILE_DATA = 0x22,
	PPC_FILE_DATA = 0x32
};

#endif
