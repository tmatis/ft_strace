#define _GNU_SOURCE

#include "param_log.h"
#include <ft_printf.h>
#include <ft_strace_utils.h>
#include <macros.h>
#include <registers.h>
#include <sys/select.h>
#include <sys/uio.h>

#define MAX_STR_LEN 32 + 1

/**
 * @brief Log argv
 *
 * @param value argv
 * @param context the context of the syscall
 * @return int the number of bytes written
 */
int log_ARGV(uint64_t value, syscall_log_param_t *context)
{
	if (value == 0)
		return ft_dprintf(STDERR_FILENO, "NULL");
	char **str_tab = (char **)value;
	int size_written = 0;
	size_written += ft_dprintf(STDERR_FILENO, "[");
	bool_t first = true;
	while (true)
	{
		char *addr_remote_str = NULL;
		struct iovec local = {
			.iov_base = &addr_remote_str,
			.iov_len = sizeof(char *),
		};
		struct iovec remote = {
			.iov_base = str_tab,
			.iov_len = sizeof(char *),
		};
		if (process_vm_readv(context->pid, &local, 1, &remote, 1, 0) < 0)
		{
			log_error("log_ARGV", "process_vm_readv failed", true);
			return 0;
		}
		if (addr_remote_str == NULL)
			break;
		if (!first)
			size_written += ft_dprintf(STDERR_FILENO, ", ");
		first = false;
		size_written += log_remote_string(context->pid, addr_remote_str, MAX_STR_LEN);
		str_tab++;
	}
	size_written += ft_dprintf(STDERR_FILENO, "]");
	return size_written;
}