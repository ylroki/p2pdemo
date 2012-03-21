#ifndef __INCLUDE_LINUX_HEADER_H__
#define __INCLUDE_LINUX_HEADER_H__

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <stddef.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/termios.h>
#include <sys/resource.h>
#include <string>
#include <string.h>
#include <vector>
#include <queue>
#include <dirent.h>
#include <stdarg.h>

#define BUF_SIZE 1024
#define THREAD_ERROR -1
typedef long long Int64;
// Some functions.
#define Min(a,b) a<b?a:b
#define Max(a,b) a>b?a:b


void ErrorQuit(const char* errString);

void Daemonize();

void DebugLog(const char* dString);

void DebugPrint(const char* dString);

void Sleep(unsigned int ms);// sleep thread amount of milliseconds

int Kbhit();
#endif
