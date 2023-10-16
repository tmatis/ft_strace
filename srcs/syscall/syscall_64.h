#pragma once

#include <syscall_strace.h>

/* here are descriptions of x86_64 syscalls
 * based on
 * https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md#x86_64-64_bit
 */

/* [SYSCALL_NO] = { "SYSCALL_NAME", RETURN_TYPE, { ARG_TYPE1, ARG_TYPE2,
 * ARG_TYPE3, ARG_TYPE4, ARG_TYPE5, ARG_TYPE6 } } */
static const syscall_description_t x86_64_syscalls[] = {
	[0] = {"read", INT, {-SIGNED_INT, MEMSEG, INT, NONE}},
	[1] = {"write", INT, {-SIGNED_INT, -MEMSEG, -INT, NONE}},
	[2] = {"open", INT, {-STRING, -OPEN_FLAGS, -OPEN_MODE, NONE}},
	[3] = {"close", INT, {-INT, NONE}},
	[4] = {"stat", INT, {-STRING, STAT_STRUCT, NONE}},
	[5] = {"fstat", INT, {-INT, STAT_STRUCT, NONE}},
	[6] = {"lstat", INT, {-STRING, STAT_STRUCT, NONE}},
	[7] = {"poll", POLL_FDS_AFTER, {-POLL_FDS, -INT, -SIGNED_INT, NONE}},
	[8] = {"lseek", INT, {-SIGNED_INT, -SIGNED_INT, -SEEK_WHENCE, NONE}},
	[9] = {"mmap", PTR, {-PTR, -INT, -MEM_PROT, -MMAP_FLAGS, -SIGNED_INT, HEX}},
	[10] = {"mprotect", INT, {-PTR, -SIGNED_INT, -MEM_PROT, NONE}},
	[11] = {"munmap", INT, {-PTR, -SIGNED_INT, NONE}},
	[12] = {"brk", PTR, {-PTR, NONE}},
	[13] = {"rt_sigaction", INT, {-SIGNAL_NAME, -SIGACTION_STRUCT, SIGACTION_STRUCT, INT}},
	[14] = {"rt_sigprocmask", INT, {-SIGPROCMASK_HOW, -SIGSET_STRUCT, SIGSET_STRUCT, INT, NONE}},
	[15] = {"rt_sigreturn", INT, {-PTR, NONE}},
	[16] = {"ioctl", INT, {-INT, -INT, -INT, NONE}},
	[17] = {"pread64", INT, {-INT, MEMSEG, INT, INT, NONE}},
	[18] = {"pwrite64", INT, {-INT, -MEMSEG, -INT, -INT, NONE}},
	[19] = {"readv", INT, {-INT, IOVEC_STRUCT, INT, NONE}},
	[20] = {"writev", INT, {-INT, -IOVEC_STRUCT, -INT, NONE}},
	[21] = {"access", INT, {-STRING, -ACCESS_MODE, NONE}},
	[22] = {"pipe", INT, {PIPEFDS, NONE}},
	[23] = {"select", SELECT_RETURN, {-INT, -FD_SET_STRUCT, -FD_SET_STRUCT, -FD_SET_STRUCT, -TIMEVAL_STRUCT}},
};