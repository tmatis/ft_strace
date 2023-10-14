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
 * @brief Handle the signal raised by the tracee
 *
 * @param pid the pid of the tracee
 */
int signals_handle(pid_t pid, int *cont_signal, analysis_routine_data_t *analysis_state)
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
	if (analysis_state->status == EXECVE_ENCOUNTERED)
	{
		ft_printf("--- %s {si_signo=%s, si_code=%s, si_pid=%d, si_uid=%d",
				  ft_signalname(siginfo.si_signo), ft_signalname(siginfo.si_signo),
				  ft_sicodename(siginfo.si_signo, siginfo.si_code), siginfo.si_pid, siginfo.si_uid);
		if (siginfo.si_signo == SIGCHLD)
			ft_printf(", si_status=%d, si_utime=%ld, si_stime=%ld", siginfo.si_status,
					  siginfo.si_utime, siginfo.si_stime);
		ft_printf("} ---\n");
	}
	*cont_signal = siginfo.si_signo;
	return SIG_RAISED;
}