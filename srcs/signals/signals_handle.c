#define _XOPEN_SOURCE
#define _XOPEN_SOURCE_EXTENDED 1

#include <analysis.h>
#include <ft_printf.h>
#include <ft_strace_utils.h>
#include <ft_string.h>
#include <signal.h>
#include <sys/ptrace.h>
#include <syscall_strace.h>

/**
 * @brief Handle signals raised by the tracee
 *
 * @param pid the pid of the tracee
 * @param cont_signal the ptr to the signal to continue the tracee
 * @param analysis_state the analysis_state of the analysis routine
 * @param should_log whether the signal should be logged
 * @return int SIG_RAISED if a signal was raised, NO_STATUS otherwise
 */
int signals_handle(pid_t pid, int *cont_signal, analysis_routine_data_t *analysis_state,
				   bool_t should_log)
{
	siginfo_t siginfo = {0};
	if (ptrace(PTRACE_GETSIGINFO, pid, 0, &siginfo) < 0)
	{
		log_error("handle_signal", "ptrace(PTRACE_GETSIGINFO) failed", true);
		return SIG_RAISED;
	}
	if (siginfo.si_signo == SIGTRAP && siginfo.si_code == TRAP_UNK)
	{
		return NO_STATUS;
	}
	if (siginfo.si_signo == SIGSTOP && siginfo.si_code != SI_TKILL)
	{
		*cont_signal = SIGSTOP;
		return SIG_RAISED;
	}
	if (should_log && analysis_state->status == EXECVE_ENCOUNTERED)
	{
		ft_dprintf(STDERR_FILENO, "--- %s {si_signo=%s, si_code=%s",
				   ft_signalname(siginfo.si_signo), ft_signalname(siginfo.si_signo),
				   ft_sicodename(siginfo.si_signo, siginfo.si_code));
		if (siginfo.si_signo == SIGSEGV)
			ft_dprintf(STDERR_FILENO, ", si_addr=%p", siginfo.si_addr);
		else
			ft_dprintf(STDERR_FILENO, ", si_pid=%d, si_uid=%d", siginfo.si_pid, siginfo.si_uid);
		if (siginfo.si_signo == SIGCHLD)
			ft_dprintf(STDERR_FILENO, ", si_status=%d, si_utime=%ld, si_stime=%ld",
					   siginfo.si_status, siginfo.si_utime, siginfo.si_stime);
		ft_dprintf(STDERR_FILENO, "} ---\n");
	}
	*cont_signal = siginfo.si_signo;
	return SIG_RAISED;
}