#pragma once

#include <bool_t.h>
#include <registers.h>
#include <stdint.h>
#include <sys/types.h>
#include <user_registers.h>

#define PADDING_SIZE 42

#define X_86_64_EXECVE_SYSCALL 59
#define X_86_32_EXECVE_SYSCALL 11

#define NONE 0
#define INT 1
#define SIGNED_INT 2
#define HEX 3
#define STRING 4
#define MEMSEG 5
#define OPEN_FLAGS 6
#define OPEN_MODE 7
#define STAT_STRUCT 8
#define POLL_FDS 9
#define POLL_FDS_AFTER 10
#define SEEK_WHENCE 11
#define PTR 12
#define MEM_PROT 13
#define MMAP_FLAGS 14
#define SIGNAL_NAME 15
#define SIGACTION_STRUCT 16
#define SIGSET_STRUCT 17
#define SIGPROCMASK_HOW 18
#define IOVEC_STRUCT 19
#define ACCESS_MODE 20
#define PIPEFDS 21
#define FD_SET_STRUCT 22
#define TIMEVAL_STRUCT 23
#define SELECT_RETURN 24
#define MREMAP_FLAGS 25
#define MSYNC_FLAGS 26
#define MADVISE_ADVISE 27

/**
 * @brief Negative if printed before the syscall, positive if printed after the
 * syscall
 *
 */
typedef int64_t arg_type_t;

typedef struct
{
	const char *name;
	const arg_type_t return_type;
	const arg_type_t arg_types[6];
} syscall_description_t;

#define MAX_SYSCALL_NO 0x17f

typedef enum
{
	EXECVE_NOT_ENCOUNTERED,
	EXECVE_ENCOUNTERED,
	EXECVE_ERROR,
} execve_status_t;

typedef struct
{
	execve_status_t status;
	register_type_t register_type;
} analysis_routine_data_t;

#define NO_STATUS -1
#define SIG_RAISED -2

/**
 * @brief Get the syscall description corresponding to the syscall number
 *
 * @param syscall_no  The syscall number
 * @return syscall_description_t*  The syscall description
 */
const syscall_description_t *syscall_get_description(uint64_t syscall_no, register_type_t type);

/**
 * @brief Log the name of the syscall and its parameters
 *
 * @param pid The pid of the process
 * @param regs_before The registers before the syscall
 * @param type the registers type
 * @return int the number of bytes written
 */
int syscall_log_name_params(pid_t pid, user_regs_t *regs_before, register_type_t register_type);

/**
 * @brief Log a syscall parameter
 *
 * @param pid the pids of the tracee
 * @param regs the registers
 * @param regs_type the registers type
 * @param arg_index the argument index
 * @return int the number of bytes written
 */
int syscall_log_param(pid_t pid, user_regs_t *regs, register_type_t regs_type, uint8_t arg_index);

/**
 * @brief Log remaining parameters of the syscall and return value
 *
 * @param pid The pid of the process
 * @param syscall_no The syscall number
 * @param regs_before_type The registers type before the syscall
 * @param regs_after The registers after the syscall
 * @param regs_after_type The registers type after the syscall
 * @param bytes_written The number of bytes written before
 */
void syscall_log_params_return(pid_t pid, int syscall_no, register_type_t regs_before_type,
							   user_regs_t *regs_after, register_type_t regs_after_type,
							   int size_written);

/**
 * @brief Log the return value of a syscall
 *
 * @param pid the pids of the tracee
 * @param regs the registers
 * @param regs_type the registers type
 */
void syscall_log_return(pid_t pid, user_regs_t *regs, register_type_t regs_type);

/**
 * @brief Check if syscall is execve depending on the syscall number and the
 * registers type
 *
 * @param syscall_no
 * @param type
 * @return bool_t true if syscall is execve, false otherwise
 */
bool_t syscall_is_execve(uint64_t syscall_no, register_type_t type);

/**
 * @brief Handle a syscall
 *
 * @param pid the pid of the tracee
 * @param analysis_state the analysis_state of the analysis routine
 * @return int the status code of the tracee or NO_STATUS if no status code is
 * available
 */
int syscall_handle(pid_t pid, analysis_routine_data_t *analysis_state, int *cont_signal);