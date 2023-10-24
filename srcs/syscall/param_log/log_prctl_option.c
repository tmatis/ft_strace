#define _GNU_SOURCE

#include <sys/prctl.h>
#include <macros.h>
#include "param_log.h"

static const flag_str_t prctl_option_flags[] = {
    FLAG_STR(PR_CAP_AMBIENT),
    FLAG_STR(PR_CAP_AMBIENT_CLEAR_ALL),
    FLAG_STR(PR_CAP_AMBIENT_IS_SET),
    FLAG_STR(PR_CAP_AMBIENT_RAISE),
    FLAG_STR(PR_CAP_AMBIENT_LOWER),
    FLAG_STR(PR_GET_DUMPABLE),
    FLAG_STR(PR_SET_DUMPABLE),
    FLAG_STR(PR_GET_KEEPCAPS),
    FLAG_STR(PR_SET_KEEPCAPS),
    FLAG_STR(PR_GET_NAME),
    FLAG_STR(PR_SET_NAME),
    FLAG_STR(PR_GET_NO_NEW_PRIVS),
    FLAG_STR(PR_SET_NO_NEW_PRIVS),
    FLAG_STR(PR_GET_PDEATHSIG),
    FLAG_STR(PR_SET_PDEATHSIG),
    FLAG_STR(PR_GET_SECCOMP),
    FLAG_STR(PR_SET_SECCOMP),
    FLAG_STR(PR_GET_SECUREBITS),
    FLAG_STR(PR_SET_SECUREBITS),
    FLAG_STR(PR_SET_TIMERSLACK),
    FLAG_STR(PR_GET_TIMERSLACK),
    FLAG_STR(PR_TASK_PERF_EVENTS_DISABLE),
    FLAG_STR(PR_TASK_PERF_EVENTS_ENABLE),
    FLAG_STR(PR_MCE_KILL),
    FLAG_STR(PR_MCE_KILL_GET),
    FLAG_STR(PR_SET_CHILD_SUBREAPER),
    FLAG_STR(PR_GET_CHILD_SUBREAPER),
    FLAG_STR(PR_SET_THP_DISABLE),
    FLAG_STR(PR_GET_THP_DISABLE),
    FLAG_STR(PR_MPX_ENABLE_MANAGEMENT),
    FLAG_STR(PR_MPX_DISABLE_MANAGEMENT),
    FLAG_STR(PR_SET_MM),
    FLAG_STR(PR_SET_MM_START_CODE),
    FLAG_STR(PR_SET_MM_END_CODE),
    FLAG_STR(PR_SET_MM_START_DATA),
    FLAG_STR(PR_SET_MM_END_DATA),
    FLAG_STR(PR_SET_MM_START_STACK),
    FLAG_STR(PR_SET_MM_START_BRK),
    FLAG_STR(PR_SET_MM_BRK),
    FLAG_STR(PR_SET_MM_ARG_START),
    FLAG_STR(PR_SET_MM_ARG_END),
    FLAG_STR(PR_SET_MM_ENV_START),
    FLAG_STR(PR_SET_MM_ENV_END),
    FLAG_STR(PR_SET_MM_AUXV),
    FLAG_STR(PR_SET_MM_EXE_FILE),
    FLAG_STR(PR_SET_MM_MAP),
    FLAG_STR(PR_SET_MM_MAP_SIZE),
};    

int log_PRCTL_OPTION(uint64_t value)
{
    return option_log(value, prctl_option_flags, ELEM_COUNT(prctl_option_flags), "ARCH_???");
}