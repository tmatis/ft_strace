#include <registers.h>

/**
 * @brief Get the param for x86_64
 *
 * @param regs the registers
 * @param param_index the param index
 * @return uint64_t the param
 */
static uint64_t registers_get_param_x86_64(user_regs_t *regs, uint8_t param_index)
{
    switch (param_index)
    {
    case 0:
        return regs->x86_64.rdi;
    case 1:
        return regs->x86_64.rsi;
    case 2:
        return regs->x86_64.rdx;
    case 3:
        return regs->x86_64.r10;
    case 4:
        return regs->x86_64.r8;
    }
    return regs->x86_64.r9;
}

/**
 * @brief Get the param for x86_32
 *
 * @param regs the registers
 * @param param_index the param index
 * @return uint64_t the param
 */
static uint64_t registers_get_param_x86_32(user_regs_t *regs, uint8_t param_index)
{
    switch (param_index)
    {
    case 0:
        return regs->x86_32.ebx;
    case 1:
        return regs->x86_32.ecx;
    case 2:
        return regs->x86_32.edx;
    case 3:
        return regs->x86_32.esi;
    case 4:
        return regs->x86_32.edi;
    }
    return regs->x86_32.ebp;
}

/**
 * @brief Get the param from registers
 *
 * @param regs the registers
 * @param type the registers type
 * @param param_index the param index
 * @return uint64_t the param
 */
uint64_t registers_get_param(user_regs_t *regs, register_type_t type, uint8_t param_index)
{
    if (type == X86_64)
        return registers_get_param_x86_64(regs, param_index);
    return registers_get_param_x86_32(regs, param_index);
}