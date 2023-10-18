#define _GNU_SOURCE

#include "param_log.h"
#include <ft_printf.h>
#include <ft_strace_utils.h>
#include <macros.h>
#include <registers.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/wait.h>

/**
 * @brief Log wait status
 * 
 * @param status the status to log
 * @return int the number of bytes written
 */
static int log_wait_status(int status)
{
	int size_written = 0;
	bool_t first = true;
	if (WIFEXITED(status))
	{
		size_written += ft_dprintf(STDERR_FILENO, "{WIFEXITED(s), WEXITSTATUS(s) == %d}",
								   WIFEXITED(status), WEXITSTATUS(status));
		first = false;
	}
	if (WIFSIGNALED(status))
	{
		size_written += ft_dprintf(STDERR_FILENO, "%s{WIFSIGNALED(s), WTERMSIG(s) == %d",
								   first ? "" : ", ", WTERMSIG(status));
		if (WCOREDUMP(status))
			size_written += ft_dprintf(STDERR_FILENO, ", WCOREDUMP(s) == %d", WCOREDUMP(status));
		size_written += ft_dprintf(STDERR_FILENO, "}");
		first = false;
	}
	if (WIFSTOPPED(status))
	{
		size_written += ft_dprintf(STDERR_FILENO, "%s{WIFSTOPPED(s), WSTOPSIG(s) == %d}",
								   first ? "" : ", ", WSTOPSIG(status));
		first = false;
	}
	if (WIFCONTINUED(status))
		size_written += ft_dprintf(STDERR_FILENO, "%s{WIFCONTINUED(s)}", first ? "" : ", ");
	return size_written;
}

/**
 * @brief Log wait status
 * 
 * @param value the ptr to wait status
 * @param context the context of the syscall
 * @return int the number of bytes written
 */
int log_WAIT_STATUS(uint64_t value, syscall_log_param_t *context)
{
	if (value == 0)
		return ft_dprintf(STDERR_FILENO, "NULL");
	if (context->after_syscall)
	{
		int64_t ret = (int64_t)registers_get_return(context->regs, context->type);
		if (ret < 0)
			return ft_dprintf(STDERR_FILENO, "%p", (void *)value);
	}
	int status;
	struct iovec local = {
		.iov_base = &status,
		.iov_len = sizeof(status),
	};
	struct iovec remote = {
		.iov_base = (void *)value,
		.iov_len = sizeof(status),
	};
	if (process_vm_readv(context->pid, &local, 1, &remote, 1, 0) < 0)
	{
		log_error("log_WAIT_STATUS", "process_vm_readv failed", true);
		return 0;
	}
	int size_written = 0;
	size_written += ft_dprintf(STDERR_FILENO, "[");
    size_written += log_wait_status(status);
	size_written += ft_dprintf(STDERR_FILENO, "]");
	return size_written;
}