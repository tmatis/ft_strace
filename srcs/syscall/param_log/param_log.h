#pragma once

#include <registers.h>
#include <stdint.h>
#include <sys/types.h>

typedef struct
{
	pid_t pid;
	uint8_t arg_index;
	user_regs_t *regs;
	register_type_t type;
} syscall_log_param_t;

typedef void (*log_function_t)();

/**
 * @brief log memory segment
 *
 * @param value the value
 * @param context the context
 */
void log_MEMSEG(uint64_t value, syscall_log_param_t *context);