#pragma once

#include <syscall_strace.h>

/* here are descriptions of x86_64 syscalls
 * based on
 * https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md#x86_64-64_bit
 */

/* [SYSCALL_NO] = { "SYSCALL_NAME", RETURN_TYPE, { ARG_TYPE1, ARG_TYPE2,
 * ARG_TYPE3, ARG_TYPE4, ARG_TYPE5, ARG_TYPE6 } } */
static const syscall_description_t x86_64_syscalls[] = {
	[0] = {"read", SIGNED_INT, {-SIGNED_INT, MEMSEG, INT, NONE}},
	[1] = {"write", SIGNED_INT, {-SIGNED_INT, -MEMSEG, -INT, NONE}},
	[2] = {"open", SIGNED_INT, {-STRING, -OPEN_FLAGS, -OPEN_MODE, NONE}},
	[3] = {"close", SIGNED_INT, {-INT, NONE}},
	[4] = {"stat", SIGNED_INT, {-STRING, STAT_STRUCT, NONE}},
	[5] = {"fstat", SIGNED_INT, {-INT, STAT_STRUCT, NONE}},
	[6] = {"lstat", SIGNED_INT, {-STRING, STAT_STRUCT, NONE}},
	[7] = {"poll", POLL_FDS_AFTER, {-POLL_FDS, -INT, -SIGNED_INT, NONE}},
	[8] = {"lseek", SIGNED_INT, {-SIGNED_INT, -SIGNED_INT, -SEEK_WHENCE, NONE}},
	[9] = {"mmap", PTR, {-PTR, -INT, -MMAP_PROT, -MMAP_FLAGS, -SIGNED_INT, HEX}}};
