#include <assert.h>
#include <ft_printf.h>
#include <ft_string.h>
#include <macros.h>
#include <param_types.h>
#include <syscall_strace.h>
#include <user_registers.h>

#define ERROR_RANGE_START 0
#define ERROR_RANGE_END 4095
#define ERESTARTSYS 512

/**
 * @brief Log the name of the syscall and its parameters
 *
 * @param pid The pid of the process
 * @param regs_before The registers before the syscall
 * @param type the registers type
 * @return int the number of bytes written
 */
int syscall_log_name_params(pid_t pid, user_regs_t *regs_before, register_type_t register_type)
{
	int size_written = 0;
	uint64_t syscall_no = registers_get_syscall(regs_before, register_type);
	const syscall_description_t *syscall_desc = syscall_get_description(syscall_no, register_type);
	size_written += ft_dprintf(STDERR_FILENO, "%s(", syscall_desc->name);
	const size_t param_count = ELEM_COUNT(syscall_desc->arg_types);
	for (uint8_t i = 0; i < param_count; i++)
	{
		if (syscall_desc->arg_types[i] == NONE || syscall_desc->arg_types[i] > 0)
			break;
		size_written += syscall_log_param(pid, regs_before, register_type, i);
		if (!(i == param_count - 1 || syscall_desc->arg_types[i + 1] == NONE))
			size_written += ft_dprintf(STDERR_FILENO, ", ");
	}
	return size_written;
}

/**
 * @brief Log remaining parameters of the syscall and return value
 *
 * @param pid The pid of the process
 * @param syscall_no The syscall number
 * @param regs_before_type The registers type before the syscall
 * @param regs_after The registers after the syscall
 * @param regs_after_type The registers type after the syscall
 * @param bytes_written The number of bytes written before
 */
void syscall_log_params_return(pid_t pid, int syscall_no, register_type_t regs_before_type,
							   user_regs_t *regs_after, register_type_t regs_after_type,
							   int size_written)
{
	const syscall_description_t *syscall_desc =
		syscall_get_description(syscall_no, regs_before_type);
	int64_t return_value = (int64_t)registers_get_return(regs_after, regs_after_type);
	int errno_value = 0;
	if (return_value < 0 && return_value >= -4096)
	{
		errno_value = -return_value;
		return_value = -1;
	}
	const size_t param_count = ELEM_COUNT(syscall_desc->arg_types);
	for (uint8_t i = 0; i < param_count; i++)
	{
		if (syscall_desc->arg_types[i] == NONE)
			break;
		if (syscall_desc->arg_types[i] < 0)
			continue;
		size_written += syscall_log_param(pid, regs_after, regs_after_type, i);
		if (!(i == param_count - 1 || syscall_desc->arg_types[i + 1] == NONE))
			size_written += ft_dprintf(STDERR_FILENO, ", ");
	}
	size_written += ft_dprintf(STDERR_FILENO, ")");
	// write padding
	ft_dprintf(STDERR_FILENO, "%*s", PADDING_SIZE - size_written, " = ");
	if (errno_value == ERESTARTSYS)
	{
		ft_dprintf(STDERR_FILENO, "?");
		ft_dprintf(STDERR_FILENO, " %s (%s)", "ERESTARTSYS",
				   "To be restarted if SA_RESTART is set");
		ft_dprintf(STDERR_FILENO, "\n");
	}
	else
	{
		syscall_log_return(pid, regs_after, regs_after_type);
		if (errno_value)
			ft_dprintf(STDERR_FILENO, " %s (%s)", ft_errnoname(errno_value),
					   ft_strerror(errno_value));
		ft_dprintf(STDERR_FILENO, "\n");
	}
}