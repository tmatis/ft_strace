#pragma once

#include <sys/types.h>
#include <syscall_strace.h>

/**
 * @brief Block signals
 * 
 */
void signals_block(void);

/**
 * @brief Unblock signals
 *
 */
void signals_unblock(void);

/**
 * @brief Handle the signal raised by the tracee
 *
 * @param pid the pid of the tracee
 */
int signals_handle(pid_t pid, int *cont_signal, analysis_routine_data_t *analysis_state);