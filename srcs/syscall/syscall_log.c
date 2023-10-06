#include <user_registers.h>
#include <syscall_strace.h>
#include <ft_printf.h>
#include <assert.h>

/**
 * @brief Log the name of the syscall and its parameters
 *
 * @param regs_before The registers before the syscall
 */
void syscall_log_name_params(pid_t pid, user_regs_x86_64_t *regs_before)
{
    int syscall_no = regs_before->orig_rax;
    const syscall_description_t *syscall_desc = syscall_get_description(syscall_no);
    ft_dprintf(STDERR_FILENO, "%s(", syscall_desc->name);
    const size_t param_count = ELEM_COUNT(syscall_desc->arg_types);
    for (uint32_t i = 0; i < param_count; i++)
    {
        if (syscall_desc->arg_types[i] == NONE)
            break;
        uint64_t arg = 0;
        switch (i)
        {
        case 0:
            arg = regs_before->rdi;
            break;
        case 1:
            arg = regs_before->rsi;
            break;
        case 2:
            arg = regs_before->rdx;
            break;
        case 3:
            arg = regs_before->r10;
            break;
        case 4:
            arg = regs_before->r8;
            break;
        case 5:
            arg = regs_before->r9;
            break;
        default:
            assert(0); // should never happen
        }
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
 */
void syscall_log_return(pid_t pid, int syscall_no, user_regs_x86_64_t *regs_after)
{
    const syscall_description_t *syscall_desc = syscall_get_description(syscall_no);
    ft_dprintf(STDERR_FILENO, ") = ");
    syscall_log_param(pid, syscall_desc->return_type, regs_after->rax);
    ft_dprintf(STDERR_FILENO, "\n");
}