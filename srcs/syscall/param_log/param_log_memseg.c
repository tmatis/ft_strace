#define _GNU_SOURCE

#include "param_log.h"
#include <ft_printf.h>
#include <ft_strace_utils.h>
#include <ft_string.h>
#include <registers.h>
#include <sys/uio.h>

#define MAX_PRINT_SIZE 32

/**
 * @brief log memory segment
 *
 * @param value the value
 * @param context the context
 */
void log_MEMSEG(uint64_t value, syscall_log_param_t *context)
{
	size_t buffer_size = registers_get_return(context->regs, context->type);
	size_t to_read = buffer_size > MAX_PRINT_SIZE ? MAX_PRINT_SIZE : buffer_size;
	char *buffer = malloc(to_read);
	struct iovec local;
	struct iovec remote;
	local.iov_base = buffer;
	local.iov_len = to_read;
	remote.iov_base = (void *)value;
	remote.iov_len = to_read;
	if (process_vm_readv(context->pid, &local, 1, &remote, 1, 0) < 0)
	{
		log_error("log_MEM", "process_vm_readv failed", true);
		return;
	}
	char *escaped_buffer = ft_escape(buffer, to_read);
	if (buffer_size > MAX_PRINT_SIZE)
		ft_dprintf(STDERR_FILENO, "\"%s\"...", escaped_buffer);
	else
		ft_dprintf(STDERR_FILENO, "\"%s\"", escaped_buffer);
	free(escaped_buffer);
	free(buffer);
}