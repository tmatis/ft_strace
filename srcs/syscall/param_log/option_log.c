#include "param_log.h"
#include <ft_printf.h>

/**
 * @brief Log a value from a list of options
 * 
 * @param value the value to log
 * @param options the list of options
 * @param options_size the size of the list of options
 * @return int the number of bytes written
 */
int option_log(uint64_t value, const flag_str_t *options, size_t options_size)
{
    for (size_t i = 0; i < options_size; i++)
    {
        if (options[i].flag == value)
            return ft_dprintf(STDERR_FILENO, "%s", options[i].str);
    }
    return ft_dprintf(STDERR_FILENO, "%#llx", value);
}