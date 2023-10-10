#include <analysis.h>
#include <errno.h>
#include <ft_printf.h>
#include <ft_strace_utils.h>
#include <signal.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <syscall_strace.h>

/**
 * @brief Handle the status of the tracee
 *
 * @param status the status of the tracee
 * @return int the status code of the tracee or NO_STATUS if no status code is
 * available
 */
static int handle_status(int status)
{
	if (status == NO_STATUS)
		return NO_STATUS;
	if (WIFEXITED(status))
	{
		ft_printf("+++ exited with %d +++\n", WEXITSTATUS(status));
		return WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		ft_printf("+++ killed by %d +++\n", WTERMSIG(status));
		return WTERMSIG(status);
	}
	return NO_STATUS;
}

/**
 * @brief Analysis routine of the tracer
 *
 * @param pid the pid of the tracee
 * @return status code of tracee or ROUTINE_ERROR if an error occurred
 */
int analysis_routine(pid_t pid)
{
	analysis_routine_data_t data = {NOT_ENCOUNTERED, X86_64};
	while (true)
	{
		int status;
		if (waitpid(pid, &status, 0) < 0)
		{
			log_error("analysis_routine", "waitpid failed", true);
			return ROUTINE_ERROR;
		}
		int status_code = handle_status(status);
		if (status_code != NO_STATUS)
			return status_code;
		status_code = handle_status(syscall_handle(pid, &data));
		if (status_code != NO_STATUS)
			return status_code;
		if (ptrace(PTRACE_SYSCALL, pid, NULL, NULL) < 0)
			continue;
	}
	return ROUTINE_ERROR;
}