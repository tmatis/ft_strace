#include <errno.h>
#include <signal.h>
#include <signals_strace.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * @brief Initial wait for the tracee
 *
 * @param pid the pid of the tracee
 * @param status the status of the tracee
 * @param flag the flag to pass to waitpid
 * @return int 0 if the call succeeded, -1 otherwise
 */
int initial_wait(pid_t pid, int *status, int flag)
{
	signals_unblock();
	if (waitpid(pid, status, flag) < 0)
	{
		int errno_save = errno;
		signals_block();
		errno = errno_save;
		return -1;
	}
	signals_block();
	return 0;
}