#pragma once

#include <bool_t.h>
#include <sys/types.h>

/**
 * @brief show a error message in STDERR
 *
 * @param context the context where the error was raised
 * @param message the error message
 * @param show_error if true, the message derivate from errno will be shown
 */
void log_error(const char *context, const char *message, bool_t show_error);

/**
 * @brief Initial wait for the tracee
 *
 * @param pid the pid of the tracee
 * @param status the status of the tracee
 * @param flag the flag to pass to waitpid
 * @return int 0 if the call succeeded, -1 otherwise
 */
int initial_wait(pid_t pid, int *status, int flag);