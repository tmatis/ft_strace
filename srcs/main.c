#include <config.h>
#include <execution.h>
#include <ft_strace_utils.h>
#include <sys/wait.h>

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
	__pid_t pid = exec_program(args.argv, envp);
	if (pid == EXEC_ERROR)
	{
		log_error("main", "exec_program failed", true);
		return 1;
	}
	waitpid(pid, 0, 0);
	return (0);
}
