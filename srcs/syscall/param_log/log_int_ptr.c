#define _GNU_SOURCE

#include "param_log.h"
#include <ft_printf.h>
#include <ft_strace_utils.h>
#include <macros.h>
#include <registers.h>
#include <sys/uio.h>

/**
 * @brief Log int ptr
 * 
 * @param value the ptr to int
 * @param context the context of the syscall
 * @return int the number of bytes written
 */
int log_INT_PTR(uint64_t value, syscall_log_param_t *context)
{
    if (value == 0)
        return ft_dprintf(STDERR_FILENO, "NULL");
    if (context->after_syscall)
    {
        int64_t ret = (int64_t)registers_get_return(context->regs, context->type);
        if (ret < 0)
            return ft_dprintf(STDERR_FILENO, "%p", (void *)value);
    }
    int local_value = 0;
    struct iovec local = {
        .iov_base = &local_value,
        .iov_len = sizeof(int),
    };
    struct iovec remote = {
        .iov_base = (void *)value,
        .iov_len = sizeof(int),
    };
    if (process_vm_readv(context->pid, &local, 1, &remote, 1, 0) < 0)
    {
        log_error("log_INT_PTR", "process_vm_readv failed", true);
        return 0;
    }
    return ft_dprintf(STDERR_FILENO, "[%d]", local_value);
}