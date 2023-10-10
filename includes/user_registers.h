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
	int ebx;
	int ecx;
	int edx;
	int esi;
	int edi;
	int ebp;
	int eax;
	int xds;
	int xes;
	int xfs;
	int xgs;
	int orig_eax;
	int eip;
	int xcs;
	int eflags;
	int esp;
	int xss;
};

/**
 * @brief Union containing the registers of a x86 or x86_64 process
 *
 */
typedef union
{
	struct user_regs_struct x86_64;
	struct i386_user_regs_struct x86_32;
} user_regs_t;