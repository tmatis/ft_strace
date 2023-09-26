#include <ft_string.h>
#include <ft_printf.h>
#include <bool_t.h>
#include <errno.h>

/**
 * @brief show a error message in STDERR
 * 
 * @param context the context where the error was raised
 * @param message the error message
 * @param show_error if true, the message derivate from errno will be shown
 */
void log_error(const char *context, const char *message, bool_t show_error)
{
    int saved_errno = errno;
    ft_dprintf(STDERR_FILENO, "%s: %s", context, message);
    if (show_error)
    {
        ft_dprintf(STDERR_FILENO, ": %s", ft_strerror(saved_errno));
    }
    ft_dprintf(STDERR_FILENO, "\n");
}