#define _GNU_SOURCE

#include "param_log.h"
#include <ft_printf.h>
#include <ft_strace_utils.h>
#include <macros.h>
#include <registers.h>
#include <sys/uio.h>
#include <sys/select.h>

/**
 * @brief Log a fd_set struct
 * 
 * @param value the ptr to fd_set
 * @param context the context of the syscall
 * @return int the number of bytes written
 */
int log_FD_SET_STRUCT(uint64_t value, syscall_log_param_t *context)
{
    if (value == 0)
        return ft_dprintf(STDERR_FILENO, "NULL");
    if (context->after_syscall)
    {
        int64_t ret = (int64_t)registers_get_return(context->regs, context->type);
        if (ret < 0)
            return ft_dprintf(STDERR_FILENO, "%p", (void *)value);
    }
    fd_set set;
    struct iovec local = {
        .iov_base = &set,
        .iov_len = sizeof(set),
    };
    struct iovec remote = {
        .iov_base = (void *)value,
        .iov_len = sizeof(set),
    };
    int nfds = registers_get_param(context->regs, context->type, 0);
    if (process_vm_readv(context->pid, &local, 1, &remote, 1, 0) < 0)
    {
        log_error("log_FD_SET", "process_vm_readv failed", true);
        return 0;
    }
    int size_written = 0;
    size_written += ft_dprintf(STDERR_FILENO, "[");
    bool_t first = true;
    for (int i = 0; i < nfds; i++)
    {
        if (FD_ISSET(i, &set))
        {
            if (!first)
                size_written += ft_dprintf(STDERR_FILENO, ", ");
            size_written += ft_dprintf(STDERR_FILENO, "%d", i);
            first = false;
        }
    }
    size_written += ft_dprintf(STDERR_FILENO, "]");
    return size_written;
}