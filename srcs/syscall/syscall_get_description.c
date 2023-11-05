#include "syscall_32.h"
#include "syscall_64.h"
#include <ft_printf.h>
#include <macros.h>
#include <syscall_strace.h>

static syscall_description_t *get_default_syscall(uint64_t syscall_no)
{
	static char default_syscall_name[32] = {0};
	static syscall_description_t default_syscall = {default_syscall_name, INT, {NONE}, NULL};
	ft_snprintf(default_syscall_name, sizeof(default_syscall_name), "unknown_%llu", syscall_no);
	return &default_syscall;
}

/**
 * @brief Get the syscall description corresponding to the syscall number
 *
 * @param syscall_no  The syscall number
 * @return syscall_description_t*  The syscall description
 */
const syscall_description_t *syscall_get_description(uint64_t syscall_no, register_type_t type)
{
	const syscall_description_t *selected_syscall;
	if (type == X86_64)
	{
		if (syscall_no >= ELEM_COUNT(x86_64_syscalls))
			return get_default_syscall(syscall_no);
		selected_syscall = &x86_64_syscalls[syscall_no];
		if (selected_syscall->name == NULL)
			return get_default_syscall(syscall_no);
	}
	else
	{
		if (syscall_no >= ELEM_COUNT(i386_syscalls))
			return get_default_syscall(syscall_no);
		selected_syscall = &i386_syscalls[syscall_no];
		if (selected_syscall->name == NULL)
			return get_default_syscall(syscall_no);
	}
	return selected_syscall;
}