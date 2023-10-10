#include <user_registers.h>
#include <syscall_strace.h>
#include <ft_printf.h>
#include <assert.h>
#include <ft_string.h>

#define ERROR_RANGE_START 0
#define ERROR_RANGE_END 4095

/**
 * @brief Log the name of the syscall and its parameters
 *
 * @param pid The pid of the process
 * @param regs_before The registers before the syscall
 * @param type the registers type
 */
void syscall_log_name_params(pid_t pid, user_regs_t *regs_before, register_type_t register_type)
{
    uint64_t syscall_no = registers_get_syscall(regs_before, register_type);
    const syscall_description_t *syscall_desc = syscall_get_description(syscall_no, register_type);
    ft_dprintf(STDERR_FILENO, "%s(", syscall_desc->name);
    const size_t param_count = ELEM_COUNT(syscall_desc->arg_types);
    for (uint8_t i = 0; i < param_count; i++)
    {
        if (syscall_desc->arg_types[i] == NONE || syscall_desc->arg_types[i] > 0)
            break;
        syscall_log_param(pid, regs_before, register_type, i);
        if (!(i == param_count - 1 || syscall_desc->arg_types[i + 1] == NONE))
            ft_dprintf(STDERR_FILENO, ", ");
    }
}

/**
 * @brief Log remaining parameters of the syscall and return value
 * 
 * @param pid The pid of the process
 * @param syscall_no The syscall number
 * @param regs_after The registers after the syscall
 * @param regs_after_type The registers type after the syscall
 */
void syscall_log_params_return(
    pid_t pid,
    int syscall_no,
    user_regs_t *regs_after,
    register_type_t regs_after_type)
{
    const syscall_description_t *syscall_desc = syscall_get_description(syscall_no, regs_after_type);
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
        syscall_log_param(pid, regs_after, regs_after_type, i);
        if (!(i == param_count - 1 || syscall_desc->arg_types[i + 1] == NONE))
            ft_dprintf(STDERR_FILENO, ", ");
    }
    ft_dprintf(STDERR_FILENO, ") = ");
    syscall_log_return(pid, regs_after, regs_after_type);
    if (errno_value)
        ft_dprintf(STDERR_FILENO, " %s (%s)", ft_errnoname(errno_value), ft_strerror(errno_value));
    ft_dprintf(STDERR_FILENO, "\n");
}