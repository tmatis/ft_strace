#pragma once

#include <stdint.h>
#include <sys/user.h>

/**
 * @brief Structure containing the registers of a x86_64 process
 *
 */
/**
 * @brief Structure containing the registers of a x86 process
 *
 */
struct i386_user_regs_struct
{
	uint32_t ebx;
	uint32_t ecx;
	uint32_t edx;
	uint32_t esi;
	uint32_t edi;
	uint32_t ebp;
	uint32_t eax;
	uint32_t xds;
	uint32_t xes;
	uint32_t xfs;
	uint32_t xgs;
	uint32_t orig_eax;
	uint32_t eip;
	uint32_t xcs;
	uint32_t eflags;
	uint32_t esp;
	uint32_t xss;
};

/**
 * @brief Union containing the registers of a x86 or x86_64 process
 *
 */
typedef union
{
	struct user_regs_struct x86_64;
	struct i386_user_regs_struct i386;
} user_regs_t;