#include "param_log.h"
#include <sys/resource.h>
#include <macros.h>
static const flag_str_t priority_flags[] = {
	FLAG_STR(PRIO_PROCESS),
	FLAG_STR(PRIO_PGRP),
	FLAG_STR(PRIO_USER),
};

int log_PRIORITY_WHICH(uint64_t uvalue)
{
	return option_log(uvalue, priority_flags, ELEM_COUNT(priority_flags), "PRIO_???");
}