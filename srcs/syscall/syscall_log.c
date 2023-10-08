#include <user_registers.h>
#include <syscall_strace.h>
#include <ft_printf.h>
#include <assert.h>
#include <ft_string.h>

/**
 * @brief Log the name of the syscall and its parameters
 *
 * @param pid The pid of the process
 * @param regs_before The registers before the syscall
 * @param type the registers type
 */
void syscall_log_name_params(pid_t pid, user_regs_t *regs_before, register_type_t type)
{
    uint64_t syscall_no = registers_get_syscall(regs_before, type);
    const syscall_description_t *syscall_desc = syscall_get_description(syscall_no, type);
    ft_dprintf(STDERR_FILENO, "%s(", syscall_desc->name);
    const size_t param_count = ELEM_COUNT(syscall_desc->arg_types);
    for (uint8_t i = 0; i < param_count; i++)
    {
        if (syscall_desc->arg_types[i] == NONE)
            break;
        uint64_t arg = registers_get_param(regs_before, type, i);
        syscall_log_param(pid, syscall_desc->arg_types[i], arg);
        if (!(i == param_count - 1 || syscall_desc->arg_types[i + 1] == NONE))
            ft_dprintf(STDERR_FILENO, ", ");
    }
}

/**
 * @brief Log the return value of the syscall
 * 
 * @param pid the pid of the process
 * @param syscall_no the syscall number
 * @param regs_after the registers after the syscall
 * @param type the registers type
 */
void syscall_log_return(pid_t pid, int syscall_no, user_regs_t *regs_after, register_type_t type)
{
    const syscall_description_t *syscall_desc = syscall_get_description(syscall_no, type);
    ft_dprintf(STDERR_FILENO, ") = ");
    int64_t return_value = (int64_t)registers_get_return(regs_after, type);
    int errno = 0;
    if (return_value < 0)
    {
        errno = -return_value;
        return_value = -1;
    }
    syscall_log_param(pid, syscall_desc->return_type, return_value);
    if (errno)
        ft_dprintf(STDERR_FILENO, " %s (%s)", ft_strerror(errno), "Not implemented");
    ft_dprintf(STDERR_FILENO, "\n");
}