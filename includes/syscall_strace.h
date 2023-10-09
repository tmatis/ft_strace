#pragma once

#include <stdint.h>
#include <user_registers.h>
#include <registers.h>
#include <sys/types.h>
#include <bool_t.h>

#define X_86_64_EXECVE_SYSCALL 59
#define X_86_32_EXECVE_SYSCALL 11

#define NONE 0
#define INT 1
#define SIGNED_INT 2
#define HEX 3
#define STRING 4

/**
 * @brief Negative if printed before the syscall, positive if printed after the syscall
 * 
 */
typedef int64_t arg_type_t;

typedef struct {
    const char *name;
    const arg_type_t return_type;
    const arg_type_t arg_types[6];
} syscall_description_t;

#define ELEM_COUNT(x) (sizeof(x) / sizeof(x[0]))

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
 * @param regs_before The registers before the syscall
 */
void syscall_log_name_params(pid_t pid, user_regs_t *regs_before, register_type_t type);

/**
 * @brief Log a parameter of the syscall
 * 
 * @param pid The pid of the process
 * @param arg_type the type of the parameter
 * @param arg the value of the parameter
 */
void syscall_log_param(pid_t pid, arg_type_t arg_type, uint64_t arg);

/**
 * @brief Log remaining parameters of the syscall and return value
 * 
 * @param pid The pid of the process
 * @param syscall_no The syscall number
 * @param regs_after The registers after the syscall
 * @param regs_after_type The registers type after the syscall
 */
void syscall_log_params_return(
    pid_t pid,
    int syscall_no,
    user_regs_t *regs_after,
    register_type_t regs_after_type);
/**
 * @brief Check if syscall is execve depending on the syscall number and the registers type
 * 
 * @param syscall_no
 * @param type 
 * @return bool_t true if syscall is execve, false otherwise
 */
bool_t syscall_is_execve(uint64_t syscall_no, register_type_t type);