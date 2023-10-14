#pragma once

#include <bool_t.h>
#include <registers.h>
#include <stdint.h>
#include <sys/types.h>

typedef struct
{
	pid_t pid;
	uint8_t arg_index;
	user_regs_t *regs;
	register_type_t type;
	bool_t after_syscall;
} syscall_log_param_t;

typedef void (*log_function_t)();

/**
 * @brief log memory segment
 *
 * @param value the value
 * @param context the context of the syscall
 */
void log_MEMSEG(uint64_t value, syscall_log_param_t *context);

/**
 * @brief Log a string
 * 
 * @param value the value
 * @param context the context of the syscall
 */
void log_STRING(uint64_t value, syscall_log_param_t *context);

/**
 * @brief Log open flags
 * 
 * @param value the value to log
 */
void log_OPEN_FLAGS(uint64_t value);

/**
 * @brief Log open mode
 * 
 * @param value the value to log
 */
void log_OPEN_MODE(uint64_t value);