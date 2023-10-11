#include "param_log/param_log.h"
#include <ft_printf.h>
#include <registers.h>
#include <sys/types.h>
#include <syscall_strace.h>

static void log_INT(uint64_t value)
{
	int64_t signed_value = (int64_t)value;
	ft_dprintf(STDERR_FILENO, "%lld", signed_value);
}

static void log_UNSIGNED_INT(uint64_t value)
{
	ft_dprintf(STDERR_FILENO, "%llu", value);
}

static void log_HEX(uint64_t value)
{
	ft_dprintf(STDERR_FILENO, "%#llx", value);
}

static void log_STRING(uint64_t value)
{
	ft_dprintf(STDERR_FILENO, "%#llx", value);
}

static void log_NONE(uint64_t value)
{
	(void)value;
	ft_dprintf(STDERR_FILENO, "?");
}

static const log_function_t log_functions[] = {
	[NONE] = log_NONE, [INT] = log_INT,		  [SIGNED_INT] = log_UNSIGNED_INT,
	[HEX] = log_HEX,   [STRING] = log_STRING, [MEMSEG] = log_MEMSEG,
};

/**
 * @brief Log a syscall parameter
 *
 * @param pid the pids of the tracee
 * @param regs the registers
 * @param regs_type the registers type
 * @param arg_index the argument index
 */
void syscall_log_param(pid_t pid, user_regs_t *regs, register_type_t regs_type, uint8_t arg_index)
{
	uint64_t syscall_no = registers_get_syscall(regs, regs_type);
	const syscall_description_t *syscall_desc = syscall_get_description(syscall_no, regs_type);
	arg_type_t arg_type = syscall_desc->arg_types[arg_index];
	if (arg_type < 0)
		arg_type = -arg_type;
	uint64_t arg = registers_get_param(regs, regs_type, arg_index);
	syscall_log_param_t param = {
		.pid = pid,
		.arg_index = arg_index,
		.regs = regs,
		.type = regs_type,
	};
	log_functions[arg_type](arg, &param);
}

/**
 * @brief Log the return value of a syscall
 *
 * @param pid the pids of the tracee
 * @param regs the registers
 * @param regs_type the registers type
 */
void syscall_log_return(pid_t pid, user_regs_t *regs, register_type_t regs_type)
{
	uint64_t syscall_no = registers_get_syscall(regs, regs_type);
	const syscall_description_t *syscall_desc = syscall_get_description(syscall_no, regs_type);
	arg_type_t return_type = syscall_desc->return_type;
	if (return_type < 0)
		return_type = -return_type;
	int64_t return_value = registers_get_return(regs, regs_type);
	if (return_value < 0 && return_value >= -4096)
	{
		ft_dprintf(STDERR_FILENO, "-1");
		return;
	}
	syscall_log_param_t param = {
		.pid = pid,
		.arg_index = -1,
		.regs = regs,
		.type = regs_type,
	};
	log_functions[return_type](return_value, &param);
}