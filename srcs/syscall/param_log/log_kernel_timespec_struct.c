#define _GNU_SOURCE

#include "param_log.h"
#include <ft_printf.h>
#include <ft_strace_utils.h>
#include <macros.h>
#include <registers.h>
#include <sys/uio.h>

typedef struct kernel_timespec
{
    long tv_sec;
    long tv_nsec;
} kernel_timespec_t;

/**
 * @brief Log a timespec struct
 * 
 * @param value the ptr to timespec
 * @param context the context of the syscall
 * @return int the number of bytes written
 */
int log_KERNEL_TIMESPEC_STRUCT(uint64_t value, syscall_log_param_t *context)
{
    if (value == 0)
        return ft_dprintf(STDERR_FILENO, "NULL");
    if (context->after_syscall)
    {
        int64_t ret = (int64_t)registers_get_return(context->regs, context->type);
        if (ret < 0)
            return ft_dprintf(STDERR_FILENO, "%p", (void *)value);
    }
    kernel_timespec_t timespec;
    struct iovec local = {
        .iov_base = &timespec,
        .iov_len = sizeof(timespec),
    };
    struct iovec remote = {
        .iov_base = (void *)value,
        .iov_len = sizeof(timespec),
    };
    if (process_vm_readv(context->pid, &local, 1, &remote, 1, 0) < 0)
    {
        log_error("log_kernel_timespec_struct", "process_vm_readv failed", true);
        return 0;
    }
    return ft_dprintf(STDERR_FILENO, "{tv_sec=%ld, tv_nsec=%ld}", timespec.tv_sec, timespec.tv_nsec);
}