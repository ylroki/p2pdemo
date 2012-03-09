#include "linux_header.h"


void ErrorQuit(const char* errString)
{
	printf("%s\n", errString);
	exit(1);
}

void DebugLog(const char* dString)
{
	int	logfd = open("/home/ylroki/project/local_repos/p2p_system/debug.log", O_RDWR | O_CREAT | O_TRUNC);
	write(logfd, dString, strlen(dString));
	close(logfd);
}

void DebugPrint(const char* dString)
{
#ifdef __DEBUG__
	printf("%s\n", dString);
#endif
}


void Daemonize()
{
	// Clear file creation mask.
	umask(0);

	// Get maximum number of file descriptors.
	struct rlimit rl;
	if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
		ErrorQuit("Can't get file limit");

	// Become a session leader to lose controlling TTY.
	pid_t pid;
	if ((pid = fork()) < 0)
		ErrorQuit("Can't fork");
	else if (pid != 0) // Parent
		exit(0);
	setsid();

	// Ensure future opens won't allocate controlling TTYs.
	struct sigaction sa;
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGHUP, &sa, NULL) < 0)
		ErrorQuit("Can't ignore SIGHUP");
	if ((pid = fork()) < 0)
		ErrorQuit("Can't fork");
	else if (pid != 0)
		exit(0);

	/* Change the current working directory to root so
	 * we won't prevent file systems form being unmounted.
	 */
	if (chdir("/") < 0)
		ErrorQuit("Can't change directory to /");
	// Close all open file descriptors
	if (rl.rlim_max == RLIM_INFINITY)
		rl.rlim_max = 1024;
	for (int i = 0; i < rl.rlim_max; ++i)
		close(i);
	
	// Attach file descriptors 0, 1 and 2 to /dev/null.
	int fd0 = open("/dev/null", O_RDWR);
	int fd1 = dup(0);
	int fd2 = dup(0);

}


