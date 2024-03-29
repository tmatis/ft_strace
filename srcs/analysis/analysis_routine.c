
#include <analysis.h>
#include <config.h>
#include <errno.h>
#include <ft_printf.h>
#include <ft_strace_utils.h>
#include <ft_string.h>
#include <signal.h>
#include <signals_strace.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <syscall_strace.h>

/**
 * @brief Handle the status of the tracee
 *
 * @param status the status of the tracee
 * @param cont_signal the ptr to the signal to continue the tracee
 * @return int the status code of the tracee or NO_STATUS if no status code is
 * available
 */
static int handle_status(pid_t pid, int status, int *cont_signal,
						 analysis_routine_data_t *analysis_state, bool_t statistic_mode)
{
	if (status == NO_STATUS)
		return NO_STATUS;
	if (WIFEXITED(status))
	{
		if (!statistic_mode)
			ft_dprintf(STDERR_FILENO, "+++ exited with %d +++\n", WEXITSTATUS(status));
		return status;
	}
	if (WIFSIGNALED(status))
	{
		if (!statistic_mode)
			ft_dprintf(STDERR_FILENO, "+++ killed by %s +++\n", ft_signalname(WTERMSIG(status)));
		return status;
	}
	if (WIFSTOPPED(status))
		return signals_handle(pid, cont_signal, analysis_state, !statistic_mode);
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
	const bool_t statistic_mode = is_option_set(OPT_MASK_STATISTICS, get_config());
	analysis_routine_data_t analysis_state = {
		.status = EXECVE_NOT_ENCOUNTERED,
		.register_type = X86_64,
	};
	int cont_signal = 0;
	while (true)
	{
		if (ptrace(PTRACE_SYSCALL, pid, NULL, cont_signal) < 0)
		{
			log_error("analysis_routine", "ptrace failed", true);
			return ROUTINE_ERROR;
		}
		cont_signal = 0;
		int status;
		if (waitpid(pid, &status, 0) < 0)
		{
			log_error("analysis_routine", "waitpid failed", true);
			return ROUTINE_ERROR;
		}
		int status_code = handle_status(pid, status, &cont_signal, &analysis_state, statistic_mode);
		if (status_code == SIG_RAISED)
			continue;
		if (status_code != NO_STATUS)
			return status_code;
		status_code =
			handle_status(pid, syscall_handle(pid, &analysis_state, &cont_signal, statistic_mode),
						  &cont_signal, &analysis_state, statistic_mode);
		if (status_code == SIG_RAISED)
			continue;
		if (status_code != NO_STATUS)
			return status_code;
	}
	return ROUTINE_ERROR;
}