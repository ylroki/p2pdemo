#ifndef __INCLUDE_COMMAND_H__
#define __INCLUDE_COMMAND_H__
#include <linux_header.h>

// Client foreground process send to Client background process.
extern const char* g_LocalCommand[];

bool IsLocalCommand(const char* command);

enum KP2PCommand
{};

#endif
