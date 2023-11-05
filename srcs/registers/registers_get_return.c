#include <registers.h>

/**
 * @brief Get the return from registers
 *
 * @param regs the registers
 * @param type the registers type
 * @return uint64_t the return
 */
uint64_t registers_get_return(user_regs_t *regs, register_type_t type)
{
	if (type == X86_64)
		return regs->x86_64.rax;
	return regs->i386.eax;
}