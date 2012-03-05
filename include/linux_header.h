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
#include <string>
#include <string.h>

#define BUF_SIZE 1024
// Some functions.
void ErrorQuit(const char* errString)
{
	printf("%s\n", errString);
	exit(1);
}

void Daemonize();

void daemon_log()
{
	int	logfd = open("/home/ylroki/project/local_repos/p2p_system/daemon.log", O_RDWR | O_CREAT | O_TRUNC);
	char buf[] = "daemondebug";
	write(logfd, buf, 11);
	close(logfd);
}
#endif
