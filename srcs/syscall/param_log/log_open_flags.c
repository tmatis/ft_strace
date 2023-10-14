#define _GNU_SOURCE

#include "param_log.h"
#include <fcntl.h>
#include <ft_printf.h>
#include <macros.h>
#include <sys/stat.h>
#include <sys/types.h>

static const flag_str_t flags[] = {
	FLAG_STR(O_RDONLY),	   FLAG_STR(O_WRONLY),	  FLAG_STR(O_RDWR),		FLAG_STR(O_CREAT),
	FLAG_STR(O_EXCL),	   FLAG_STR(O_NOCTTY),	  FLAG_STR(O_TRUNC),	FLAG_STR(O_APPEND),
	FLAG_STR(O_NONBLOCK),  FLAG_STR(O_DSYNC),	  FLAG_STR(O_ASYNC),	FLAG_STR(O_DIRECT),
	FLAG_STR(O_LARGEFILE), FLAG_STR(O_DIRECTORY), FLAG_STR(O_NOFOLLOW), FLAG_STR(O_NOATIME),
	FLAG_STR(O_CLOEXEC),   FLAG_STR(O_PATH),	  FLAG_STR(O_TMPFILE),
};

/**
 * @brief Log open flags
 *
 * @param value the value to log
 */
int log_OPEN_FLAGS(uint64_t value)
{
	int size_written = 0;
	bool_t first = true;
	for (size_t i = 0; i < ELEM_COUNT(flags); i++)
	{
		if (value & flags[i].flag)
		{
			if (!first)
				size_written += ft_dprintf(STDERR_FILENO, "|");
			size_written += ft_dprintf(STDERR_FILENO, "%s", flags[i].str);
			first = false;
			value &= ~flags[i].flag;
		}
	}
	if (value)
	{
		if (!first)
			size_written += ft_dprintf(STDERR_FILENO, "|");
		size_written += ft_dprintf(STDERR_FILENO, "%#llx", value);
	}
	return size_written;
}