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

typedef struct
{
	uint64_t flag;
	const char *str;
} flag_str_t;

#define FLAG_STR(flag)                                                                             \
	{                                                                                              \
		flag, #flag                                                                                \
	}

typedef int (*log_function_t)();

/**
 * @brief log memory segment
 *
 * @param value the value
 * @param context the context of the syscall
 */
int log_MEMSEG(uint64_t value, syscall_log_param_t *context);

/**
 * @brief Log a string
 *
 * @param value the value
 * @param context the context of the syscall
 */
int log_STRING(uint64_t value, syscall_log_param_t *context);

/**
 * @brief Log open flags
 *
 * @param value the value to log
 */
int log_OPEN_FLAGS(uint64_t value);

/**
 * @brief Log open mode
 *
 * @param value the value to log
 */
int log_OPEN_MODE(uint64_t value);

/**
 * @brief Log stat struct
 *
 * @param value
 * @param context
 * @return int
 */
int log_STAT_STRUCT(uint64_t value, syscall_log_param_t *context);

/**
 * @brief Log poll fds
 * 
 * @param value 
 * @param context 
 * @return int 
 */
int log_POLL_FDS(uint64_t value, syscall_log_param_t *context);

/**
 * @brief Log poll fds
 *
 * @param value
 * @param context
 * @return int
 */
int log_POLL_FDS_AFTER(uint64_t value, syscall_log_param_t *context);

/**
 * @brief Log whence
 * 
 * @param value the value to log
 * @return int the number of bytes written
 */
int log_SEEK_WHENCE(uint64_t value);