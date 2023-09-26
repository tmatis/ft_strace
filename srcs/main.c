#include <config.h>

int main(int argc, char **argv)
{
	config_t *config = get_config();
	args_t args;
	
	if (parse_args(argc, argv, &args, config))
	{
		display_help();
		return 1;
	}
	if (is_option_set(OPT_MASK_HELP, config))
	{
		display_help();
		return 0;
	}
	return (0);
}
