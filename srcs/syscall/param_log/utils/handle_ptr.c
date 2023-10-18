#include "../param_log.h"
#include <stdint.h>
#include <ft_printf.h>

/**
 * @brief Handle a pointer value
 * 
 * @param value the pointer value
 * @param context the syscall context
 * @param size_written the number of bytes written
 * @return void* 
 */
void *handle_ptr(uint64_t value, syscall_log_param_t *context, int *size_written)
{
	if (value == 0)
	{
        *size_written += ft_dprintf(STDERR_FILENO, "NULL");
        return NULL;
    }
	if (context->after_syscall)
	{
		int64_t ret = (int64_t)registers_get_return(context->regs, context->type);
		if (ret < 0)
		{
            *size_written += ft_dprintf(STDERR_FILENO, "%p", (void *)value);
            return NULL;
        }
	}
	return (void *)value;
}