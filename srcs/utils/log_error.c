#include <bool_t.h>
#include <config.h>
#include <errno.h>
#include <ft_printf.h>
#include <ft_string.h>

/**
 * @brief show a error message in STDERR
 *
 * @param context the context where the error was raised
 * @param message the error message
 * @param show_error if true, the message derivate from errno will be shown
 */
void log_error(const char *context, const char *message, bool_t show_error)
{
	config_t *config = get_config();
	int saved_errno = errno;
	ft_dprintf(STDERR_FILENO, "%s: %s: %s", config->program_name, context, message);
	if (show_error)
		ft_dprintf(STDERR_FILENO, ": %s", ft_strerror(saved_errno));
	ft_dprintf(STDERR_FILENO, "\n");
}