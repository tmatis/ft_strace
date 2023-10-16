#include <analysis.h>
#include <config.h>
#include <execution.h>
#include <ft_printf.h>
#include <ft_strace_utils.h>
#include <signal.h>
#include <signals_strace.h>

int main(int argc, char **argv, char **envp)
{
	config_t *config = get_config();
	args_t args;

	if (parse_args(argc, argv, &args, config) || args.argc == 0)
	{
		display_help();
		return 1;
	}
	if (is_option_set(OPT_MASK_HELP, config))
	{
		display_help();
		return 0;
	}
	pid_t pid = exec_program(args.argv, envp);

	if (pid == EXEC_CHILD_END)
		return 1;
	if (pid == EXEC_ERROR)
	{
		log_error("main", "exec_program failed", true);
		return 1;
	}
	if (setup_tracing(pid))
		return 1;
	int status = analysis_routine(pid);
	if (status == ROUTINE_ERROR)
		return 1;
	signals_unblock();
	if (WIFSIGNALED(status))
		raise(WTERMSIG(status));
	return WEXITSTATUS(status);
}
