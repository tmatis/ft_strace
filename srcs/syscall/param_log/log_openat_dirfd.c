#include "param_log.h"
#include <ft_printf.h>
#include <macros.h>
#include <fcntl.h>

int log_OPENAT_DIRFD(int value)
{
    if (value == AT_FDCWD)
        return ft_dprintf(STDERR_FILENO, "AT_FDCWD");
    return ft_dprintf(STDERR_FILENO, "%d", value);
}