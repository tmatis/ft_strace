#define _GNU_SOURCE

#include <sys/mount.h>
#include "param_log.h"
#include <macros.h>

static const flag_str_t mount_flags[] = {
    FLAG_STR(MS_RDONLY),
    FLAG_STR(MS_NOSUID),
    FLAG_STR(MS_NODEV),
    FLAG_STR(MS_NOEXEC),
    FLAG_STR(MS_SYNCHRONOUS),
    FLAG_STR(MS_REMOUNT),
    FLAG_STR(MS_MANDLOCK),
    FLAG_STR(MS_DIRSYNC),
    FLAG_STR(MS_NOATIME),
    FLAG_STR(MS_NODIRATIME),
    FLAG_STR(MS_BIND),
    FLAG_STR(MS_MOVE),
    FLAG_STR(MS_REC),
    FLAG_STR(MS_SILENT),
    FLAG_STR(MS_POSIXACL),
    FLAG_STR(MS_UNBINDABLE),
    FLAG_STR(MS_PRIVATE),
    FLAG_STR(MS_SLAVE),
    FLAG_STR(MS_SHARED),
    FLAG_STR(MS_RELATIME),
    FLAG_STR(MS_KERNMOUNT),
    FLAG_STR(MS_I_VERSION),
    FLAG_STR(MS_STRICTATIME),
    FLAG_STR(MS_LAZYTIME),
    FLAG_STR(MS_ACTIVE),
    FLAG_STR(MS_NOUSER),
    FLAG_STR(MS_MGC_VAL),
    FLAG_STR(MS_MGC_MSK),
    FLAG_STR(MS_RMT_MASK),
    FLAG_STR(MS_MGC_MSK),  
};

int log_MOUNT_FLAGS(uint64_t value)
{
    return flags_log(value, mount_flags, ELEM_COUNT(mount_flags));
}