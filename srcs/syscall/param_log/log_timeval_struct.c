#define _GNU_SOURCE

#include "param_log.h"
#include <ft_printf.h>
#include <ft_strace_utils.h>
#include <macros.h>
#include <registers.h>
#include <sys/uio.h>
#include <sys/select.h>

/**
 * @brief log a timeval struct
 * 
 * @param value the ptr to timeval struct
 * @param context the context of the syscall
 * @return int the number of bytes written
 */
int log_TIMEVAL_STRUCT(uint64_t value, syscall_log_param_t *context)
{
    if (value == 0)
        return ft_dprintf(STDERR_FILENO, "NULL");
    if (context->after_syscall)
    {
        int64_t ret = (int64_t)registers_get_return(context->regs, context->type);
        if (ret < 0)
            return ft_dprintf(STDERR_FILENO, "%p", (void *)value);
    }
    struct timeval tv;
    struct iovec local = {
        .iov_base = &tv,
        .iov_len = sizeof(tv),
    };
    struct iovec remote = {
        .iov_base = (void *)value,
        .iov_len = sizeof(tv),
    };
    if (process_vm_readv(context->pid, &local, 1, &remote, 1, 0) < 0)
    {
        log_error("log_TIMEVAL_STRUCT", "process_vm_readv failed", true);
        return 0;
    }
    if (context->is_return_log && tv.tv_sec == 0 && tv.tv_usec == 0)
        return ft_dprintf(STDERR_FILENO, "(Timeout)");
    return ft_dprintf(STDERR_FILENO, "{tv_sec=%ld, tv_usec=%ld}", tv.tv_sec, tv.tv_usec);
}