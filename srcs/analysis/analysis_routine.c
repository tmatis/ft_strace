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

struct user_regs_struct_x86_64
{
    unsigned long long int r15;
    unsigned long long int r14;
    unsigned long long int r13;
    unsigned long long int r12;
    unsigned long long int rbp;
    unsigned long long int rbx;
    unsigned long long int r11;
    unsigned long long int r10;
    unsigned long long int r9;
    unsigned long long int r8;
    unsigned long long int rax;
    unsigned long long int rcx;
    unsigned long long int rdx;
    unsigned long long int rsi;
    unsigned long long int rdi;
    unsigned long long int orig_rax;
    unsigned long long int rip;
    unsigned long long int cs;
    unsigned long long int eflags;
    unsigned long long int rsp;
    unsigned long long int ss;
    unsigned long long int fs_base;
    unsigned long long int gs_base;
    unsigned long long int ds;
    unsigned long long int es;
    unsigned long long int fs;
    unsigned long long int gs;
    };

#define MAX_SYSCALL_NO 0x14c


void print_params(struct user_regs_struct_x86_64 *regs)
{
    for (int i = 0; i < 6; i++)
        ft_printf("%#llx ", regs->rdi + i * sizeof(long long int));
    ft_printf("\n");
}

#define NO_STATUS -1

int handle_syscall(pid_t pid)
{
    struct user_regs_struct_x86_64 regs;


    // before the syscall
    if (ptrace(PTRACE_GETREGS, pid, NULL, &regs) < 0)
    {
        log_error("handle_syscall", "ptrace(PTRACE_GETREGS)(1) failed", true);
        return NO_STATUS;
    }
    if (regs.orig_rax > MAX_SYSCALL_NO)
        return NO_STATUS;
    ft_printf("registers before syscall:\n");
    ft_printf("syscall %lli: ", regs.orig_rax);
    print_params(&regs);

    
    // after the syscall
    if (ptrace(PTRACE_SYSCALL, pid, NULL, NULL) < 0)
    {
        log_error("handle_syscall", "ptrace failed", true);
        return NO_STATUS;
    }
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status) || WIFSIGNALED(status))
        return status;

    // after the syscall
    if (ptrace(PTRACE_GETREGS, pid, NULL, &regs) < 0)
    {
        log_error("handle_syscall", "ptrace(PTRACE_GETREGS)(2) failed", true);
        return NO_STATUS;
    }
    ft_printf("registers after syscall:\n");
    print_params(&regs);
    ft_printf("return value: %lli\n", regs.rax);
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
        status_code = handle_status(handle_syscall(pid));
        if (status_code != NO_STATUS)
            return status_code;
        if (ptrace(PTRACE_SYSCALL, pid, NULL, NULL) < 0)
            continue;
    }
    return ROUTINE_ERROR;
}