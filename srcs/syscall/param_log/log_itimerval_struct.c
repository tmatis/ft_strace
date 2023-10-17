#define _GNU_SOURCE

#include "param_log.h"
#include <ft_printf.h>
#include <ft_strace_utils.h>
#include <macros.h>
#include <registers.h>
#include <sys/time.h>
#include <sys/uio.h>

/**
 * @brief Log a itimerval struct
 * 
 * @param value the ptr to itimerval
 * @param context the context of the syscall
 * @return int the number of bytes written
 */
int log_ITIMERVAL_STRUCT(uint64_t value, syscall_log_param_t *context)
{
	if (value == 0)
		return ft_dprintf(STDERR_FILENO, "NULL");
	if (context->after_syscall)
	{
		int64_t ret = (int64_t)registers_get_return(context->regs, context->type);
		if (ret < 0)
			return ft_dprintf(STDERR_FILENO, "%p", (void *)value);
	}
	struct itimerval itimerval;
	struct iovec local = {
		.iov_base = &itimerval,
		.iov_len = sizeof(itimerval),
	};
	struct iovec remote = {
		.iov_base = (void *)value,
		.iov_len = sizeof(itimerval),
	};
	if (process_vm_readv(context->pid, &local, 1, &remote, 1, 0) < 0)
	{
		log_error("log_ITIMERVAL_STRUCT", "process_vm_readv failed", true);
		return 0;
	}
	return ft_dprintf(STDERR_FILENO,
					  "{it_interval={tv_sec=%ld, tv_usec=%ld}, it_value={tv_sec=%ld, tv_usec=%ld}}",
					  itimerval.it_interval.tv_sec, itimerval.it_interval.tv_usec,
					  itimerval.it_value.tv_sec, itimerval.it_value.tv_usec);
}