#include <elf.h>
#include <ft_printf.h>
#include <ft_strace_utils.h>
#include <signals_strace.h>
#include <sys/ptrace.h>
#include <sys/uio.h>
#include <sys/wait.h>
#include <syscall_strace.h>

/**
 * @brief Handle the syscall before it is executed
 *
 * @param pid the pid of the tracee
 * @param analysis_state the analysis_state of the analysis routine
 * @param syscall_no the syscall number pointer to be filled
 * @param is_execve pointer to be filled with whether the syscall is an execve
 * @return int NO_STATUS if the caller must return, 1 if the syscall must be
 * logged, 0 otherwise
 */
static int handle_before_syscall(pid_t pid, analysis_routine_data_t *analysis_state, uint64_t *syscall_no,
								 bool_t *is_execve, int *size_written)
{
	user_regs_t regs_before;
	struct iovec regs_before_iov;

	regs_before_iov.iov_base = &regs_before;
	regs_before_iov.iov_len = sizeof(regs_before);
	if (ptrace(PTRACE_GETREGSET, pid, (void *)NT_PRSTATUS, &regs_before_iov) < 0)
	{
		log_error("handle_syscall", "ptrace(PTRACE_GETREGS)(1) failed", true);
		return NO_STATUS;
	}
	register_type_t register_type_before = registers_get_type(regs_before_iov.iov_len);
	if (analysis_state->register_type != register_type_before)
	{
		analysis_state->register_type = register_type_before;
		ft_dprintf(STDERR_FILENO, "[ Process PID=%d runs in 32 bit mode. ]\n", pid);
	}
	*syscall_no = registers_get_syscall(&regs_before, register_type_before);
	if (*syscall_no > MAX_SYSCALL_NO)
		return NO_STATUS;
	*is_execve = syscall_is_execve(*syscall_no, register_type_before);
	if (analysis_state->status == EXECVE_ERROR && !*is_execve)
		return NO_STATUS;
	if (analysis_state->status == EXECVE_NOT_ENCOUNTERED && !*is_execve)
		return NO_STATUS;
	bool_t should_log = analysis_state->status == EXECVE_ENCOUNTERED || (analysis_state->status != EXECVE_ERROR && *is_execve);
	if (should_log)
		*size_written = syscall_log_name_params(pid, &regs_before, register_type_before);
	return should_log;
}

/**
 * @brief Handle the syscall after it is executed
 *
 * @param pid the pid of the tracee
 * @param analysis_state the analysis_state of the analysis routine
 * @param syscall_no the syscall number
 * @param should_log whether the syscall should be logged
 * @param is_execve whether the syscall is an execve
 * @return int NO_STATUS in every case
 */
static int handle_syscall_after(pid_t pid, analysis_routine_data_t *analysis_state, uint64_t syscall_no,
								int should_log, bool_t is_execve, int size_written)
{
	user_regs_t regs_after;
	struct iovec regs_after_iov;

	regs_after_iov.iov_base = &regs_after;
	regs_after_iov.iov_len = sizeof(regs_after);
	if (ptrace(PTRACE_GETREGSET, pid, (void *)NT_PRSTATUS, &regs_after_iov) < 0)
	{
		log_error("handle_syscall", "ptrace(PTRACE_GETREGS)(2) failed", true);
		return NO_STATUS;
	}
	register_type_t register_type_after = registers_get_type(regs_after_iov.iov_len);
	if (analysis_state->status == EXECVE_NOT_ENCOUNTERED && is_execve)
		analysis_state->status = (int64_t)registers_get_return(&regs_after, register_type_after) < 0
						   ? EXECVE_ERROR
						   : EXECVE_ENCOUNTERED;
	if (should_log)
		syscall_log_params_return(pid, syscall_no, &regs_after, register_type_after, size_written);
	return NO_STATUS;
}

/**
 * @brief Handle a syscall
 *
 * @param pid the pid of the tracee
 * @param analysis_state the analysis_state of the analysis routine
 * @return int the status code of the tracee or NO_STATUS if no status code is
 * available
 */
int syscall_handle(pid_t pid, analysis_routine_data_t *analysis_state, int *cont_signal)
{
	uint64_t syscall_no;
	bool_t is_execve;
	int size_written = 0;
	int should_log = handle_before_syscall(pid, analysis_state, &syscall_no, &is_execve, &size_written);
	if (should_log == NO_STATUS)
		return NO_STATUS;
	if (ptrace(PTRACE_SYSCALL, pid, NULL, *cont_signal) < 0)
	{
		log_error("handle_syscall", "ptrace failed", true);
		return NO_STATUS;
	}
	*cont_signal = 0;
	int status;
	if (waitpid(pid, &status, 0) < 0)
	{
		log_error("handle_syscall", "waitpid failed", true);
		return NO_STATUS;
	}
	if (WIFEXITED(status) || WIFSIGNALED(status))
	{
		ft_dprintf(STDERR_FILENO, ")%*s", PADDING_SIZE - size_written - 1, " = ");
		ft_dprintf(STDERR_FILENO, "?\n");
		return status;
	}
	return handle_syscall_after(pid, analysis_state, syscall_no, should_log, is_execve, size_written);
}