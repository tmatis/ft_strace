#define _GNU_SOURCE

#include "param_log.h"
#include <ft_printf.h>
#include <macros.h>
#include <sys/ipc.h>
#include <sys/shm.h>

static const flag_str_t shmget_flags[] = {
    FLAG_STR(SHM_R),
    FLAG_STR(SHM_W),
    FLAG_STR(SHM_HUGETLB),
    FLAG_STR(SHM_NORESERVE),
    FLAG_STR(SHM_REMAP),
    FLAG_STR(SHM_EXEC),
    FLAG_STR(SHM_LOCK),
    FLAG_STR(SHM_UNLOCK),
    FLAG_STR(SHM_RDONLY),
    FLAG_STR(SHM_RND),
    FLAG_STR(SHM_REMAP),
    FLAG_STR(SHM_EXEC),
    FLAG_STR(SHM_LOCK),
    FLAG_STR(SHM_UNLOCK),
    FLAG_STR(SHM_RDONLY),
    FLAG_STR(SHM_RND),
};

/**
 * @brief Log shmget flags
 * 
 * @param value the value to log
 * @return int the number of bytes written
 */
int log_SHMGET_FLAGS(uint64_t value)
{
    return flags_log(value, shmget_flags, ELEM_COUNT(shmget_flags));
}