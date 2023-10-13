#include <analysis.h>
#include <errno.h>
#include <ft_printf.h>
#include <ft_strace_utils.h>
#include <signal.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <syscall_strace.h>
#include <ft_string.h>

/**
 * @brief Handle the status of the tracee
 *
 * @param status the status of the tracee
 * @param cont_signal the ptr to the signal to continue the tracee
 * @return int the status code of the tracee or NO_STATUS if no status code is
 * available
 */
static int handle_status(int status, int *cont_signal)
{
	*cont_signal = 0;
	if (status == NO_STATUS)
		return NO_STATUS;
	if (WIFEXITED(status))
	{
		ft_printf("+++ exited with %d +++\n", WEXITSTATUS(status));
		return status;
	}
	if (WIFSIGNALED(status))
	{
		ft_printf("+++ killed by %s +++\n", ft_signalname(WTERMSIG(status)));
		return status;
	}
	if (WIFSTOPPED(status))
	{
		int sig = WSTOPSIG(status);
		if (sig == SIGTRAP || sig == SIGSTOP || sig == SIGTSTP || sig == SIGTTIN || sig == SIGTTOU)
			return NO_STATUS;
		*cont_signal = sig;
		return SIG_RAISED;
	}
	return NO_STATUS;
}

/**
 * @brief Handle the signal raised by the tracee
 * 
 * @param pid the pid of the tracee
 */
static void handle_signal(pid_t pid)
{
	siginfo_t siginfo = {0};
	if (ptrace(PTRACE_GETSIGINFO, pid, 0, &siginfo) < 0)
	{
		log_error("handle_signal", "ptrace(PTRACE_GETSIGINFO) failed", true);
		return;
	}
	ft_printf("--- %s {si_signo=%s, si_code=%s, si_pid=%d, si_uid=%d} ---\n",
			  ft_signalname(siginfo.si_signo),
			  ft_signalname(siginfo.si_signo),
			  ft_sicodename(siginfo.si_signo, siginfo.si_code),
			  siginfo.si_pid,
			  siginfo.si_uid);

}

/**
 * @brief Analysis routine of the tracer
 *
 * @param pid the pid of the tracee
 * @return status code of tracee or ROUTINE_ERROR if an error occurred
 */
int analysis_routine(pid_t pid)
{
	analysis_routine_data_t data = {
		.status = NOT_ENCOUNTERED,
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
		int status;
		if (waitpid(pid, &status, 0) < 0)
		{
			log_error("analysis_routine", "waitpid failed", true);
			return ROUTINE_ERROR;
		}
		int status_code = handle_status(status, &cont_signal);
		if (status_code == SIG_RAISED)
		{
			handle_signal(pid);
			continue;
		}
		if (status_code != NO_STATUS)
			return status_code;
		status_code = handle_status(syscall_handle(pid, &data, cont_signal), &cont_signal);
		if (status_code == SIG_RAISED)
		{
			handle_signal(pid);
			continue;
		}
		if (status_code != NO_STATUS)
			return status_code;
	}
	return ROUTINE_ERROR;
}