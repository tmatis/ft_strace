#include <sys/ptrace.h>
#include <bool_t.h>
#include <sys/types.h>
#include <stddef.h>
#include <sys/wait.h>
#include <ft_printf.h>
#include <analysis.h>
#include <signal.h>
#include <ft_strace_utils.h>
#include <errno.h>
#include <syscall_strace.h>
#include <user_registers.h>

#define MAX_SYSCALL_NO 0x14c

#define SYS_EXECVE 0x3b

typedef enum
{
    NOT_ENCOUNTERED,
    ENCOUNTERED,
    ERROR
} execve_status_t;

typedef struct
{
    execve_status_t status;
} analysis_routine_data_t;

#define NO_STATUS -1

int handle_syscall(pid_t pid, analysis_routine_data_t *data)
{
    user_regs_x86_64_t regs_before;
    user_regs_x86_64_t regs_after;

    // before the syscall
    if (ptrace(PTRACE_GETREGS, pid, NULL, &regs_before) < 0)
    {
        log_error("handle_syscall", "ptrace(PTRACE_GETREGS)(1) failed", true);
        return NO_STATUS;
    }
    int syscall_no = regs_before.orig_rax;
    if (syscall_no > MAX_SYSCALL_NO)
        return NO_STATUS;

    // after the syscall
    if (ptrace(PTRACE_SYSCALL, pid, NULL, NULL) < 0)
    {
        log_error("handle_syscall", "ptrace failed", true);
        return NO_STATUS;
    }
    if (data->status == ERROR && syscall_no != SYS_EXECVE)
        return NO_STATUS;
    if (data->status == NOT_ENCOUNTERED && syscall_no != SYS_EXECVE)
        return NO_STATUS;
    if (data->status == NOT_ENCOUNTERED && syscall_no == SYS_EXECVE)
        data->status = regs_after.rax < 0 ? ERROR : ENCOUNTERED;
    bool_t should_log = data->status == ENCOUNTERED || (data->status != ERROR && syscall_no == SYS_EXECVE);
    if (should_log)
        syscall_log_name_params(pid, &regs_before);
    int status;
    if (waitpid(pid, &status, 0) < 0)
    {
        log_error("handle_syscall", "waitpid failed", true);
        return NO_STATUS;
    }
    if (WIFEXITED(status) || WIFSIGNALED(status))
    {
        ft_dprintf(STDERR_FILENO, ") = ?\n");
        return status;
    }

    // after the syscall
    if (ptrace(PTRACE_GETREGS, pid, NULL, &regs_after) < 0)
    {
        log_error("handle_syscall", "ptrace(PTRACE_GETREGS)(2) failed", true);
        return NO_STATUS;
    }
    if (should_log)
        syscall_log_return(pid, syscall_no, &regs_after);
    return NO_STATUS;
}

int handle_status(int status)
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
    analysis_routine_data_t data = {NOT_ENCOUNTERED};
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
        status_code = handle_status(handle_syscall(pid, &data));
        if (status_code != NO_STATUS)
            return status_code;
        if (ptrace(PTRACE_SYSCALL, pid, NULL, NULL) < 0)
            continue;
    }
    return ROUTINE_ERROR;
}