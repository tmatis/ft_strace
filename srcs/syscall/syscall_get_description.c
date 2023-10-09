#include <syscall_strace.h>
#include "syscall_64.h"
#include "syscall_32.h"

/**
 * @brief Get the syscall description corresponding to the syscall number
 * 
 * @param syscall_no  The syscall number
 * @return syscall_description_t*  The syscall description
 */
const syscall_description_t *syscall_get_description(uint64_t syscall_no, register_type_t type)
{
    static const syscall_description_t default_syscall = {"unknown", INT, {NONE, NONE, NONE, NONE, NONE, NONE}};
    // check if in bounds
    if (syscall_no >= ELEM_COUNT(x86_64_syscalls))
        return &default_syscall;
    if (type == X86_64)
        return &x86_64_syscalls[syscall_no];
    return &x86_32_syscalls[syscall_no];
}