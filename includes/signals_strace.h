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
 * @brief Handle signals raised by the tracee
 *
 * @param pid the pid of the tracee
 * @param cont_signal the ptr to the signal to continue the tracee
 * @param analysis_state the analysis_state of the analysis routine
 * @param should_log whether the signal should be logged
 * @return int SIG_RAISED if a signal was raised, NO_STATUS otherwise
 */
int signals_handle(pid_t pid, int *cont_signal, analysis_routine_data_t *analysis_state,
				   bool_t should_log);
