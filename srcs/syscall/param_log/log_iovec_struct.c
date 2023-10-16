#define _GNU_SOURCE

#include "param_log.h"
#include <ft_printf.h>
#include <ft_strace_utils.h>
#include <macros.h>
#include <registers.h>
#include <sys/uio.h>

#define NO_SIZE -1

/**
 * @brief Log iov_base
 *
 * @param pid the pid of the remote process
 * @param iov the iovec struct
 * @param is_fail true if syscall failed
 * @return int the number of bytes written
 */
static int log_iov_base(pid_t pid, struct iovec *iov, bool_t is_fail, uint64_t len)
{
	if (iov->iov_base == 0)
		return ft_dprintf(STDERR_FILENO, "NULL");
	if (is_fail)
		return ft_dprintf(STDERR_FILENO, "%p", iov->iov_base);
	return log_memseg_remote(pid, iov->iov_base, len);
}

/**
 * @brief Check if syscall failed
 *
 * @param context the context of the syscall
 * @return bool_t true if syscall failed
 */
static bool_t is_fail(syscall_log_param_t *context)
{
	if (context->after_syscall)
		return (int64_t)registers_get_return(context->regs, context->type) < 0;
	return false; // always false before syscall
}

/**
 * @brief Get the len needed to log
 *
 * @param iov the iovec struct
 * @param context the context of the syscall
 * @return uint64_t the len needed to log
 */
static uint64_t get_len(struct iovec *iov, syscall_log_param_t *context, int64_t *total_len)
{
	if (context->after_syscall)
	{
		int64_t to_log = MIN(iov->iov_len, (uint64_t)*total_len);
		*total_len -= to_log;
		return to_log;
	}
	return iov->iov_len;
}

/**
 * @brief Log iovec struct
 *
 * @param value the pointer to the iovec struct in remote process
 * @param context the context of the syscall
 * @return int the number of bytes written
 */
int log_IOVEC_STRUCT(uint64_t value, syscall_log_param_t *context)
{
	if (value == 0)
		return ft_dprintf(STDERR_FILENO, "NULL");
	uint64_t vlen = registers_get_param(context->regs, context->type, context->arg_index + 1);
	struct iovec *iov = malloc(sizeof(struct iovec) * vlen);
	if (iov == NULL)
	{
		log_error("log_IOVEC_STRUCT", "malloc failed", true);
		return 0;
	}
	struct iovec local = {
		.iov_base = iov,
		.iov_len = sizeof(struct iovec) * vlen,
	};
	struct iovec remote = {
		.iov_base = (void *)value,
		.iov_len = sizeof(struct iovec) * vlen,
	};
	int64_t total_len = NO_SIZE;
	if (context->after_syscall)
		total_len = registers_get_return(context->regs, context->type);
	if (process_vm_readv(context->pid, &local, 1, &remote, 1, 0) < 0)
	{
		log_error("log_IOVEC_STRUCT", "process_vm_readv failed", true);
		free(iov);
		return 0;
	}
	int size_written = 0;
	size_written += ft_dprintf(STDERR_FILENO, "[");
	bool_t first = true;
	for (uint64_t i = 0; i < vlen; i++)
	{
		if (!first)
			size_written += ft_dprintf(STDERR_FILENO, ", ");
		first = false;
		size_written += ft_dprintf(STDERR_FILENO, "{");
		size_written += ft_dprintf(STDERR_FILENO, ".iov_base=");
		size_written += log_iov_base(context->pid, &iov[i], is_fail(context),
									 get_len(&iov[i], context, &total_len));
		size_written += ft_dprintf(STDERR_FILENO, ", .iov_len=%lu", iov[i].iov_len);
		size_written += ft_dprintf(STDERR_FILENO, "}");
	}
	size_written += ft_dprintf(STDERR_FILENO, "]");
	free(iov);
	return size_written;
}
