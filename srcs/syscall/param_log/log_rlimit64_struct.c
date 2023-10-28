#define _GNU_SOURCE

#include "param_log.h"
#include <ft_printf.h>
#include <macros.h>
#include <sys/resource.h>

static const flag_str_t rlimit_max[] = {
	FLAG_STR(RLIM64_INFINITY),
};

static int log_rlimit_cur(uint64_t value)
{
	uint64_t n_block = value / 1024;
	uint64_t n_byte = value % 1024;
	if (n_block == 0 || n_byte != 0)
		return ft_dprintf(STDERR_FILENO, "%lu", value);
	return ft_dprintf(STDERR_FILENO, "%lu*1024", n_block);
}

int log_RLIMIT64_STRUCT(uint64_t value, syscall_log_param_t *context)
{
    STRUCT_HANDLE(struct rlimit64, rlimit);
    int size_written = 0;
    size_written += ft_dprintf(STDERR_FILENO, "{rlim_cur=");
    size_written += log_rlimit_cur(rlimit.rlim_cur);
    size_written += ft_dprintf(STDERR_FILENO, ", rlim_max=");
    size_written += option_log(rlimit.rlim_max, rlimit_max, ELEM_COUNT(rlimit_max), NULL);
    size_written += ft_dprintf(STDERR_FILENO, "}");
    return size_written;
}