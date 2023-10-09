#pragma once

#include <syscall_strace.h>

/* here are descriptions of x86_64 syscalls */
/* based on https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md#x86_64-64_bit */

/* [SYSCALL_NO] = { "SYSCALL_NAME", RETURN_TYPE, { ARG_TYPE1, ARG_TYPE2, ARG_TYPE3, ARG_TYPE4, ARG_TYPE5, ARG_TYPE6 } } */
static const syscall_description_t x86_64_syscalls[] = {
    [0] = {"read", SIGNED_INT, {-SIGNED_INT, STRING, INT, NONE}}
};
