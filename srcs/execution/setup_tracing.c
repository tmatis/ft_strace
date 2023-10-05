#include <stdlib.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <ft_strace_utils.h>
#include <sys/wait.h>

/**
 * @brief Setup tracing for tracee
 *
 * @param pid the pid of the tracee
 * @return 1 if an error occurred, 0 otherwise
 */
int setup_tracing(pid_t pid)
{
    if (waitpid(pid, NULL, WUNTRACED) < 0)
    {
        log_error("setup_tracing", "waitpid failed", true);
        return 1;
    }
    // PTRACE_SEIZE attach the tracee without stopping it
    if (ptrace(PTRACE_SEIZE, pid, NULL, NULL) < 0)
    {
        log_error("setup_tracing", "ptrace failed", true);
        return 1;
    }
    // PTRACE_SETOPTIONS set the options for the tracee
    if (ptrace(PTRACE_SETOPTIONS, pid, NULL, PTRACE_O_TRACESYSGOOD) < 0)
    {
        log_error("setup_tracing", "ptrace failed", true);
        return 1;
    }
    // PTRACE_INTERRUPT send SIGSTOP to the tracee
    if (ptrace(PTRACE_INTERRUPT, pid, NULL, NULL) < 0)
    {
        log_error("setup_tracing", "ptrace failed", true);
        return 1;
    }
    return 0;
}