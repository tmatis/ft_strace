#include "param_log.h"
#include <ft_printf.h>
#include <macros.h>
#include <linux/ioprio.h>

static const flag_str_t ioprio_which[] = {
    FLAG_STR(IOPRIO_WHO_PROCESS),
    FLAG_STR(IOPRIO_WHO_PGRP),
    FLAG_STR(IOPRIO_WHO_USER),
};

int log_IOPRIO_WHICH(uint64_t value)
{
    return flags_log(value, ioprio_which, ELEM_COUNT(ioprio_which));
}