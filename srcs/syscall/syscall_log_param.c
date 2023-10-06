#include <syscall_strace.h>
#include <ft_printf.h>
#include <sys/types.h>

static void log_INT(uint64_t value)
{
    int64_t signed_value = (int64_t)value;
    ft_dprintf(STDERR_FILENO, "%lld", signed_value);
}

static void log_UNSIGNED_INT(uint64_t value)
{
    ft_dprintf(STDERR_FILENO, "%llu", value);
}

static void log_HEX(uint64_t value)
{
    ft_dprintf(STDERR_FILENO, "%#llx", value);
}

static void log_STRING(uint64_t value)
{
    ft_dprintf(STDERR_FILENO, "%#llx", value);
}

static void log_NONE(uint64_t value)
{
    (void)value;
    ft_dprintf(STDERR_FILENO, "?");
}

typedef void (*log_function_t)(uint64_t);

/**
 * @brief Log a parameter of the syscall
 *
 * @param pid The pid of the process
 * @param arg_type the type of the parameter
 * @param arg the value of the parameter
 */
void syscall_log_param(pid_t pid, arg_type_t arg_type, uint64_t arg)
{
    (void)pid;
    static const log_function_t log_functions[] = {
        [INT] = log_INT,
        [SIGNED_INT] = log_UNSIGNED_INT,
        [HEX] = log_HEX,
        [STRING] = log_STRING,
        [NONE] = log_NONE
    };
    log_functions[arg_type](arg);
}