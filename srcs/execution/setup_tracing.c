#include <ft_printf.h>
#include <ft_strace_utils.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <unistd.h>

/**
 * @brief Setup tracing for tracee
 *
 * @param pid the pid of the tracee
 * @return 1 if an error occurred, 0 otherwise
 */
int setup_tracing(pid_t pid)
{
	// PTRACE_SEIZE attach the tracee without stopping it
	if (ptrace(PTRACE_SEIZE, pid, NULL, NULL) < 0)
	{
		log_error("setup_tracing", "ptrace(PTRACE_SEIZE) failed", true);
		return 1;
	}
	if (ptrace(PTRACE_INTERRUPT, pid, NULL, NULL) < 0)
	{
		log_error("setup_tracing", "ptrace(PTRACE_INTERRUPT) failed", true);
		return 1;
	}
	if (initial_wait(pid, NULL, 0) < 0)
	{
		log_error("setup_tracing", "initial_wait failed", true);
		return 1;
	}
	return 0;
}