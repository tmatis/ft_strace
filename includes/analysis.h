#pragma once

#include <stddef.h>
#include <sys/types.h>

#define ROUTINE_ERROR -1

/**
 * @brief Analysis routine of the tracer
 *
 * @param pid the pid of the tracee
 * @return status code of tracee or ROUTINE_ERROR if an error occurred
 */
int analysis_routine(pid_t pid);