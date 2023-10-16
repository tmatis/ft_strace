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
	bool_t is_return_log;
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
 * @brief Log a set of flags
 *
 * @param flags the flags to log
 * @param flag_strs the flags strings
 * @param flag_strs_size the size of the flag strings array
 * @return int the number of bytes written
 */
int flags_log(uint64_t flags, const flag_str_t *flag_strs, size_t flag_strs_size);

/**
 * @brief Log a value from a list of options
 *
 * @param value the value to log
 * @param options the list of options
 * @param options_size the size of the list of options
 * @param default_name the default name to use if the value is not found
 * @return int the number of bytes written
 */
int option_log(uint64_t value, const flag_str_t *options, size_t options_size,
			   const char *default_name);

/**
 * @brief log a hexadecimal value
 *
 * @param value
 * @return int
 */
int log_HEX(uint64_t value);

/**
 * @brief Log an unsigned integer
 *
 * @param value value to log
 * @return int number of bytes written
 */
int log_INT(uint64_t value);

/**
 * @brief Log an unsigned integer
 *
 * @param value value to log
 * @return int number of bytes written
 */
int log_SIGNED_INT(int64_t value);

/**
 * @brief Log an unsigned integer
 *
 * @param value value to log
 * @return int number of bytes written
 */
int log_PTR(uint64_t value);

/**
 * @brief Log ?
 *
 * @return int number of bytes written
 */
int log_NONE(void);

/**
 * @brief Log a memory segment from a remote process
 *
 * @param pid the pid of the remote process
 * @param remote_ptr the pointer to the memory segment in the remote process
 * @param buffer_size the size of the memory segment
 * @return int
 */
int log_memseg_remote(pid_t pid, void *remote_ptr, size_t buffer_size);

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

/**
 * @brief Log mmap protection flags
 *
 * @param value the value to log
 * @return int the number of bytes written
 */
int log_MEM_PROT(uint64_t value);

/**
 * @brief Log mmap flags
 *
 * @param value the value to log
 * @return int the number of bytes written
 */
int log_MMAP_FLAGS(uint64_t value);

/**
 * @brief Log a signal name
 *
 * @param value
 * @return int
 */
int log_SIGNAL_NAME(uint64_t value);

/**
 * @brief log sigaction struct
 *
 * @param value
 * @return int
 */
int log_SIGACTION_STRUCT(uint64_t value, syscall_log_param_t *context);

/**
 * @brief Log sigset in local memory
 *
 * @param sigset
 * @return int
 */
int log_local_sigset_struct(sigset_t *sigset);

/**
 * @brief log a sigset_t struct
 *
 * @param value
 * @param context
 * @return int
 */
int log_SIGSET_STRUCT(uint64_t value, syscall_log_param_t *context);

/**
 * @brief Log sigprocmask how
 *
 * @param value the value to log
 * @return int the number of bytes written
 */
int log_SIGPROCMASK_HOW(uint64_t value);

/**
 * @brief Log iovec struct
 *
 * @param value the pointer to the iovec struct in remote process
 * @param context the context of the syscall
 * @return int the number of bytes written
 */
int log_IOVEC_STRUCT(uint64_t value, syscall_log_param_t *context);

/**
 * @brief Log access mode flags
 *
 * @param value the value to log
 * @return int the number of bytes written
 */
int log_ACCESS_MODE(uint64_t value);

/**
 * @brief Log pipe fds
 * 
 * @param value the ptr to fds
 * @param context the context of the syscall
 * @return int the number of bytes written
 */
int log_PIPEFDS(uint64_t value, syscall_log_param_t *context);

/**
 * @brief Log a fd_set struct
 * 
 * @param value the ptr to fd_set
 * @param context the context of the syscall
 * @return int the number of bytes written
 */
int log_FD_SET_STRUCT(uint64_t value, syscall_log_param_t *context);

/**
 * @brief log a timeval struct
 * 
 * @param value the ptr to timeval struct
 * @param context the context of the syscall
 * @return int the number of bytes written
 */
int log_TIMEVAL_STRUCT(uint64_t value, syscall_log_param_t *context);

/**
 * @brief Log select return
 * 
 * @param value return value
 * @param context the context of the syscall
 * @return int the number of bytes written
 */
int log_SELECT_RETURN(uint64_t value, syscall_log_param_t *context);

/**
 * @brief log mremap flags
 * 
 * @param value the value to log
 * @return int the number of bytes written
 */
int log_MREMAP_FLAGS(uint64_t value);

/**
 * @brief Log msync flags
 * 
 * @param value the value to log
 * @return int the number of bytes written
 */
int log_MSYNC_FLAGS(uint64_t value);

/**
 * @brief Log madvise advice
 * 
 * @param value the value to log
 * @return int the number of bytes written
 */
int log_MADVISE_ADVISE(uint64_t value);