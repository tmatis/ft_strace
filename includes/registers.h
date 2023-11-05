#pragma once

#include <stddef.h>
#include <user_registers.h>

typedef enum
{
	I386,
	X86_64
} register_type_t;

/**
 * @brief Get registers type from size
 *
 * @param size the registers size
 * @return register_type_t the registers type
 */
register_type_t registers_get_type(size_t size);

/**
 * @brief Get the syscall no from registers
 *
 * @param regs the registers
 * @param type the registers type
 * @return uint64_t the syscall no
 */
uint64_t registers_get_syscall(user_regs_t *regs, register_type_t type);

/**
 * @brief Get the param from registers
 *
 * @param regs the registers
 * @param type the registers type
 * @param param_index the param index
 * @return uint64_t the param
 */
uint64_t registers_get_param(user_regs_t *regs, register_type_t type, uint8_t param_index);

/**
 * @brief Get the return from registers
 *
 * @param regs the registers
 * @param type the registers type
 * @return uint64_t the return
 */
uint64_t registers_get_return(user_regs_t *regs, register_type_t type);

#define REGISTERS_GET_RETURN(regs, type)                                                            \
	(type == X86_64 ? (int64_t)registers_get_return(regs, type)                                     \
					: (int32_t)registers_get_return(regs, type))