#include "param_log/param_log.h"
#include <ft_printf.h>
#include <macros.h>
#include <registers.h>
#include <sys/types.h>
#include <syscall_strace.h>

#define ADD_LOGGER(name) [name] = log_##name

static const log_function_t log_functions[] = {
	ADD_LOGGER(NONE),
	ADD_LOGGER(INT),
	ADD_LOGGER(SIGNED_INT),
	ADD_LOGGER(HEX),
	ADD_LOGGER(STRING),
	ADD_LOGGER(MEMSEG),
	ADD_LOGGER(OPEN_FLAGS),
	ADD_LOGGER(OPEN_MODE),
	ADD_LOGGER(STAT_STRUCT),
	ADD_LOGGER(POLL_FDS),
	ADD_LOGGER(POLL_FDS_AFTER),
	ADD_LOGGER(SEEK_WHENCE),
	ADD_LOGGER(PTR),
	ADD_LOGGER(MEM_PROT),
	ADD_LOGGER(MMAP_FLAGS),
	ADD_LOGGER(SIGNAL_NAME),
	ADD_LOGGER(SIGACTION_STRUCT),
	ADD_LOGGER(SIGSET_STRUCT),
	ADD_LOGGER(SIGPROCMASK_HOW),
	ADD_LOGGER(IOVEC_STRUCT),
	ADD_LOGGER(ACCESS_MODE),
};

typedef int (*log_function_with_param_t)(uint64_t value, syscall_log_param_t *context);

/**
 * @brief Log a syscall parameter
 *
 * @param pid the pids of the tracee
 * @param regs the registers
 * @param regs_type the registers type
 * @param arg_index the argument index
 * @return int the number of bytes written
 */
int syscall_log_param(pid_t pid, user_regs_t *regs, register_type_t regs_type, uint8_t arg_index)
{
	uint64_t syscall_no = registers_get_syscall(regs, regs_type);
	const syscall_description_t *syscall_desc = syscall_get_description(syscall_no, regs_type);
	arg_type_t arg_type = syscall_desc->arg_types[arg_index];
	bool_t after_syscall = true;
	if (arg_type < 0)
	{
		arg_type = -arg_type;
		after_syscall = false;
	}
	uint64_t arg = registers_get_param(regs, regs_type, arg_index);
	syscall_log_param_t param = {
		.pid = pid,
		.arg_index = arg_index,
		.regs = regs,
		.type = regs_type,
		.after_syscall = after_syscall,
	};
	if (arg_type < (int)ELEM_COUNT(log_functions))
		return ((log_function_with_param_t)log_functions[arg_type])(arg, &param);
	else
		return ft_dprintf(STDERR_FILENO, "?");
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
		.after_syscall = true,
	};
	if (return_type < (int)ELEM_COUNT(log_functions))
		((log_function_with_param_t)log_functions[return_type])(return_value, &param);
	else
		ft_dprintf(STDERR_FILENO, "?");
}