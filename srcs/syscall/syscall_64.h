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
	[23] = {"select",
			SELECT_RETURN,
			{-INT, -FD_SET_STRUCT, -FD_SET_STRUCT, -FD_SET_STRUCT, -TIMEVAL_STRUCT}},
	[24] = {"sched_yield", INT, {NONE}},
	[25] = {"mremap", INT, {-PTR, -INT, -INT, -MREMAP_FLAGS, -INT}},
	[26] = {"msync", INT, {-PTR, -INT, -MSYNC_FLAGS, NONE}},
	[27] = {"mincore", INT, {-PTR, -INT, -PTR, NONE}},
	[28] = {"madvise", INT, {-PTR, -INT, -MADVISE_ADVISE, NONE}},
	[29] = {"shmget", INT, {-HEX, -INT, -IPCS_FLAGS, NONE}},
	[30] = {"shmat", PTR, {-INT, -PTR, -SHMAT_FLAGS, NONE}},
	[31] = {"shmctl", INT, {-INT, -SHMCTL_CMD, SHMID_DS_STRUCT, NONE}},
	[32] = {"dup", INT, {-INT, NONE}},
	[33] = {"dup2", INT, {-INT, -INT, NONE}},
	[34] = {"pause", INT, {NONE}},
	[35] = {"nanosleep", INT, {-KERNEL_TIMESPEC_STRUCT, PTR, NONE}},
	[36] = {"getitimer", INT, {-ITIMER_WHICH, ITIMERVAL_STRUCT, NONE}},
	[37] = {"alarm", INT, {-INT, NONE}},
	[38] = {"setitimer", INT, {-ITIMER_WHICH, -ITIMERVAL_STRUCT, ITIMERVAL_STRUCT, NONE}},
	[39] = {"getpid", INT, {NONE}},
	[40] = {"sendfile", INT, {-SIGNED_INT, -SIGNED_INT, -PTR, -INT, NONE}},
	[41] = {"socket", INT, {-ADDRESS_FAMILY, -SOCKET_TYPE, -IPPROTO, NONE}},
	[42] = {"connect", INT, {-SIGNED_INT, -SOCKADDR_STRUCT, -INT, NONE}},
	[43] = {"accept", INT, {-INT, SOCKADDR_STRUCT, PTR, NONE}},
	[44] = {"sendto", INT, {-INT, -MEMSEG, -INT, -SEND_FLAGS, -SOCKADDR_STRUCT, -INT}},
	[45] = {"recvfrom", INT, {-INT, MEMSEG, INT, SEND_FLAGS, SOCKADDR_STRUCT, INT_PTR}},
	[46] = {"sendmsg", INT, {-INT, -MSGHDR_STRUCT, -SEND_FLAGS, NONE}},
	[47] = {"recvmsg", INT, {-INT, MSGHDR_STRUCT, SEND_FLAGS, NONE}},
	[48] = {"shutdown", INT, {-INT, -SHUTDOWN_HOW, -NONE}},
	[49] = {"bind", INT, {-INT, -SOCKADDR_STRUCT, -INT}},
	[50] = {"listen", INT, {-INT, -INT, NONE}},
	[51] = {"getsockname", INT, {-INT, SOCKADDR_STRUCT, INT_PTR, NONE}},
	[52] = {"getpeername", INT, {-INT, SOCKADDR_STRUCT, INT_PTR, NONE}},
	[53] = {"socketpair", INT, {-ADDRESS_FAMILY, -SOCKET_TYPE, -IPPROTO, -PIPEFDS, NONE}},
	[54] = {"setsockopt", INT, {-INT, -INT, -INT, -MEMSEG, -INT, NONE}},
	[55] = {"setsockopt", INT, {-INT, -INT, -INT, MEMSEG, INT_PTR, NONE}},
	[56] = {"clone", INT, {-INT, -INT, INT_PTR, INT_PTR, INT, NONE}},
	[57] = {"fork", INT, {NONE}},
	[58] = {"vfork", INT, {NONE}},
	[59] = {"execve", INT, {-STRING, -ARGV, -ENVP, NONE}},
	[60] = {"exit", INT, {-INT, NONE}},
	[61] = {"wait4", INT, {-INT, WAIT_STATUS, WAIT_OPTIONS, RUSAGE_STRUCT}},
	[62] = {"kill", INT, {-INT, -SIGNAL_NAME}},
	[63] = {"uname", INT, {UTSNAME_STRUCT, NONE}},
	[64] = {"semget", INT, {-HEX, -INT, -IPCS_FLAGS, NONE}},
	[65] = {"semop", INT, {-INT, -SEMBUF_STRUCT, -INT, NONE}},
	[66] = {"semctl", INT, {-INT, -INT, -SEMCTL_CMD, -HEX, NONE}},
	[67] = {"shmdt", INT, {-PTR, NONE}},
	[68] = {"msgget", INT, {-HEX, -IPCS_FLAGS, NONE}},
	[69] = {"msgsnd", INT, {-INT, -MSGBUF_STRUCT, -INT, -MSGFLG, NONE}},
	[70] = {"msgrcv", INT, {-INT, MSGBUF_STRUCT, INT, INT, MSGFLG, NONE}},
	[71] = {"msgctl", INT, {-INT, -MSGCTL_CMD, MSQID_DS_STRUCT, NONE}},
	[72] = {"fcntl", INT, {-INT, -FCNTL_CMD, -HEX, NONE}},
	[73] = {"flock", INT, {-INT, -FLOCK_CMD, NONE}},
	[74] = {"fsync", INT, {-INT, NONE}},
	[75] = {"fdatasync", INT, {-INT, NONE}},
	[76] = {"truncate", INT, {-STRING, -INT, NONE}},
	[77] = {"ftruncate", INT, {-INT, -INT, NONE}},
	[78] = {"getdents", INT, {-INT, PTR, INT, NONE}},
	[79] = {"getcwd", INT, {STRING, INT, NONE}},
	[80] = {"chdir", INT, {-STRING, NONE}},
	[81] = {"fchdir", INT, {-INT, NONE}},
	[82] = {"rename", INT, {-STRING, -STRING, NONE}},
	[83] = {"mkdir", INT, {-STRING, -OPEN_MODE, NONE}},
	[84] = {"rmdir", INT, {-STRING, NONE}},
	[85] = {"creat", INT, {-STRING, -OPEN_MODE, NONE}},
	[86] = {"link", INT, {-STRING, -STRING, NONE}},
	[87] = {"unlink", INT, {-STRING, NONE}},
	[88] = {"symlink", INT, {-STRING, -STRING, NONE}},
	[89] = {"readlink", INT, {-STRING, MEMSEG, INT, NONE}},
	[90] = {"chmod", INT, {-STRING, -OPEN_MODE, NONE}},
	[91] = {"fchmod", INT, {-INT, -OPEN_MODE, NONE}},
	[92] = {"chown", INT, {-STRING, -INT, -INT, NONE}},
	[93] = {"fchown", INT, {-INT, -INT, -INT, NONE}},
	[94] = {"lchown", INT, {-STRING, -INT, -INT, NONE}},
	[95] = {"umask", INT, {-OPEN_MODE, NONE}},
	[96] = {"gettimeofday", INT, {TIMEVAL_STRUCT, TIMEZONE_STRUCT, NONE}},
	[97] = {"getrlimit", INT, {-RLIMIT_RESOURCE, RLIMIT_STRUCT, NONE}},
	[98] = {"getrusage", INT, {-RUSAGE_WHO, RUSAGE_STRUCT, NONE}},
	[99] = {"sysinfo", INT, {SYSINFO_STRUCT, NONE}},
	[100] = {"times", INT, {TMS_STRUCT, NONE}},
};