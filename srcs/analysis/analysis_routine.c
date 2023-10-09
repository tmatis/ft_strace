#include <sys/ptrace.h>
#include <bool_t.h>
#include <sys/types.h>
#include <stddef.h>
#include <sys/wait.h>
#include <stdio.h>
#include <analysis.h>
#include <signal.h>
#include <ft_strace_utils.h>
#include <errno.h>
#include <syscall_strace.h>
#include <user_registers.h>
#include <sys/uio.h>
#include <elf.h>
#include <registers.h>
#include <ft_printf.h>

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
    register_type_t register_type;
} analysis_routine_data_t;

#define NO_STATUS -1

int handle_syscall(pid_t pid, analysis_routine_data_t *data)
{
    user_regs_t regs_before = {0};
    struct iovec regs_before_iov;

    regs_before_iov.iov_base = &regs_before;
    regs_before_iov.iov_len = sizeof(regs_before);
    if (ptrace(PTRACE_GETREGSET, pid, (void *)NT_PRSTATUS, &regs_before_iov) < 0)
    {
        log_error("handle_syscall", "ptrace(PTRACE_GETREGS)(1) failed", true);
        return NO_STATUS;
    }
    register_type_t register_type_before = registers_get_type(regs_before_iov.iov_len);
    if (data->register_type != register_type_before)
    {
        data->register_type = register_type_before;
        ft_dprintf(STDERR_FILENO, "[ Process PID=%d runs in 32 bit mode. ]\n", pid);
    }
    uint64_t syscall_no = registers_get_syscall(&regs_before, register_type_before);
    if (syscall_no > MAX_SYSCALL_NO)
        return NO_STATUS;

    if (ptrace(PTRACE_SYSCALL, pid, NULL, NULL) < 0)
    {
        log_error("handle_syscall", "ptrace failed", true);
        return NO_STATUS;
    }
    bool_t is_execve = syscall_is_execve(syscall_no, register_type_before);
    if (data->status == ERROR && !is_execve)
        return NO_STATUS;
    if (data->status == NOT_ENCOUNTERED && !is_execve)
        return NO_STATUS;
    bool_t should_log = data->status == ENCOUNTERED || (data->status != ERROR && is_execve);
    if (should_log)
        syscall_log_name_params(pid, &regs_before, register_type_before);
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
    user_regs_t regs_after;
    struct iovec regs_after_iov;

    regs_after_iov.iov_base = &regs_after;
    regs_after_iov.iov_len = sizeof(regs_after);
    if (ptrace(PTRACE_GETREGSET, pid, (void *)NT_PRSTATUS, &regs_after_iov) < 0)
    {
        log_error("handle_syscall", "ptrace(PTRACE_GETREGS)(2) failed", true);
        return NO_STATUS;
    }
    register_type_t register_type_after = registers_get_type(regs_after_iov.iov_len);
    if (data->status == NOT_ENCOUNTERED && syscall_no == SYS_EXECVE)
        data->status = (int64_t)registers_get_return(&regs_after, register_type_after) < 0 ? ERROR : ENCOUNTERED;
    if (should_log)
        syscall_log_params_return(pid, syscall_no, &regs_after, register_type_after);
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
        status_code = handle_status(handle_syscall(pid, &data));
        if (status_code != NO_STATUS)
            return status_code;
        if (ptrace(PTRACE_SYSCALL, pid, NULL, NULL) < 0)
            continue;
    }
    return ROUTINE_ERROR;
}