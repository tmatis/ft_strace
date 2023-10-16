#define _GNU_SOURCE

#include "param_log.h"
#include <ft_printf.h>
#include <ft_strace_utils.h>
#include <macros.h>
#include <sys/uio.h>
#include <unistd.h>

/**
 * @brief Log pipe fds
 * 
 * @param value the ptr to fds
 * @param context the context of the syscall
 * @return int the number of bytes written
 */
int log_PIPEFDS(uint64_t value, syscall_log_param_t *context)
{
    if (value == 0)
        return ft_dprintf(STDERR_FILENO, "NULL");
    if (context->after_syscall)
    {
        int64_t ret = (int64_t)registers_get_return(context->regs, context->type);
        if (ret < 0)
            return ft_dprintf(STDERR_FILENO, "%p", (void *)value);
    }
    int fds[2];
    struct iovec local = {
        .iov_base = fds,
        .iov_len = sizeof(fds),
    };
    struct iovec remote = {
        .iov_base = (void *)value,
        .iov_len = sizeof(fds),
    };
    if (process_vm_readv(context->pid, &local, 1, &remote, 1, 0) < 0)
    {
        log_error("log_PIPEFDS", "process_vm_readv failed", true);
        return 0;
    }
    return ft_dprintf(STDERR_FILENO, "[%ld, %ld]", fds[0], fds[1]);
}