#include <registers.h>

/**
 * @brief Get the syscall no from registers
 *
 * @param regs the registers
 * @param type the registers type
 * @return uint64_t the syscall no
 */
uint64_t registers_get_syscall(user_regs_t *regs, register_type_t type)
{
	if (type == X86_64)
		return regs->x86_64.orig_rax;
	return regs->x86_32.orig_eax;
}