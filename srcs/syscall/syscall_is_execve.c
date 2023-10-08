#include <registers.h>
#include <ft_test.h>
#include <bool_t.h>
#include <syscall_strace.h>

/**
 * @brief Check if syscall is execve depending on the syscall number and the registers type
 * 
 * @param syscall_no
 * @param type 
 * @return bool_t true if syscall is execve, false otherwise
 */
bool_t syscall_is_execve(uint64_t syscall_no, register_type_t type)
{
    if (type == X86_64)
        return syscall_no == X_86_64_EXECVE_SYSCALL;
    return syscall_no == X_86_32_EXECVE_SYSCALL;
}