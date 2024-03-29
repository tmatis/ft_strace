#pragma once

#include <syscall_strace.h>
#include <param_types.h>
#include "custom_handlers/custom_handler.h"

/* here are descriptions of x86_64 syscalls
 * based on
 * https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md#x86_64-64_bit
 */

/* [SYSCALL_NO] = { "SYSCALL_NAME", RETURN_TYPE, { ARG_TYPE1, ARG_TYPE2,
 * ARG_TYPE3, ARG_TYPE4, ARG_TYPE5, ARG_TYPE6 } } */
static const syscall_description_t x86_64_syscalls[] = {
	[0] = {"read", INT, {-SIGNED_INT, MEMSEG, INT, NONE}, NULL},
	[1] = {"write", INT, {-SIGNED_INT, -MEMSEG, -INT, NONE}, NULL},
	[2] = {"open", INT, {-STRING, -OPEN_FLAGS, -OPEN_MODE, NONE}, NULL},
	[3] = {"close", INT, {-INT, NONE}, NULL},
	[4] = {"stat", INT, {-STRING, STAT_STRUCT, NONE}, NULL},
	[5] = {"fstat", INT, {-INT, STAT_STRUCT, NONE}, NULL},
	[6] = {"lstat", INT, {-STRING, STAT_STRUCT, NONE}, NULL},
	[7] = {"poll", POLL_FDS_AFTER, {-POLL_FDS, -INT, -SIGNED_INT, NONE}, NULL},
	[8] = {"lseek", INT, {-SIGNED_INT, -SIGNED_INT, -SEEK_WHENCE, NONE}, NULL},
	[9] = {"mmap", PTR, {-PTR, -INT, -MEM_PROT, -MMAP_FLAGS, -SIGNED_INT, HEX}, NULL},
	[10] = {"mprotect", INT, {-PTR, -SIGNED_INT, -MEM_PROT, NONE}, NULL},
	[11] = {"munmap", INT, {-PTR, -SIGNED_INT, NONE}, NULL},
	[12] = {"brk", PTR, {-PTR, NONE}, NULL},
	[13] = {"rt_sigaction", INT, {-SIGNAL_NAME, -SIGACTION_STRUCT, SIGACTION_STRUCT, INT, NONE}, NULL},
	[14] = {"rt_sigprocmask", INT, {-SIGPROCMASK_HOW, -SIGSET_STRUCT, SIGSET_STRUCT, INT, NONE}, NULL},
	[15] = {"rt_sigreturn", INT, {-PTR, NONE}, NULL},
	[16] = {"ioctl", INT, {-INT, -INT, -INT, NONE}, NULL},
	[17] = {"pread64", INT, {-INT, MEMSEG, INT, INT, NONE}, NULL},
	[18] = {"pwrite64", INT, {-INT, -MEMSEG, -INT, -INT, NONE}, NULL},
	[19] = {"readv", INT, {-INT, IOVEC_STRUCT, INT, NONE}, NULL},
	[20] = {"writev", INT, {-INT, -IOVEC_STRUCT, -INT, NONE}, NULL},
	[21] = {"access", INT, {-STRING, -ACCESS_MODE, NONE}, NULL},
	[22] = {"pipe", INT, {PIPEFDS, NONE}, NULL},
	[23] = {"select",
			SELECT_RETURN,
			{-INT, -FD_SET_STRUCT, -FD_SET_STRUCT, -FD_SET_STRUCT, -TIMEVAL_STRUCT}, NULL},
	[24] = {"sched_yield", INT, {NONE}, NULL},
	[25] = {"mremap", INT, {-PTR, -INT, -INT, -MREMAP_FLAGS, -INT}, NULL},
	[26] = {"msync", INT, {-PTR, -INT, -MSYNC_FLAGS, NONE}, NULL},
	[27] = {"mincore", INT, {-PTR, -INT, -PTR, NONE}, NULL},
	[28] = {"madvise", INT, {-PTR, -INT, -MADVISE_ADVISE, NONE}, NULL},
	[29] = {"shmget", INT, {-HEX, -INT, -IPCS_FLAGS, NONE}, NULL},
	[30] = {"shmat", PTR, {-INT, -PTR, -SHMAT_FLAGS, NONE}, NULL},
	[31] = {"shmctl", INT, {-INT, -SHMCTL_CMD, SHMID_DS_STRUCT, NONE}, NULL},
	[32] = {"dup", INT, {-INT, NONE}, NULL},
	[33] = {"dup2", INT, {-INT, -INT, NONE}, NULL},
	[34] = {"pause", INT, {NONE}, NULL},
	[35] = {"nanosleep", INT, {-KERNEL_TIMESPEC_STRUCT, PTR, NONE}, NULL},
	[36] = {"getitimer", INT, {-ITIMER_WHICH, ITIMERVAL_STRUCT, NONE}, NULL},
	[37] = {"alarm", INT, {-INT, NONE}, NULL},
	[38] = {"setitimer", INT, {-ITIMER_WHICH, -ITIMERVAL_STRUCT, ITIMERVAL_STRUCT, NONE}, NULL},
	[39] = {"getpid", INT, {NONE}, NULL},
	[40] = {"sendfile", INT, {-SIGNED_INT, -SIGNED_INT, -PTR, -INT, NONE}, NULL},
	[41] = {"socket", INT, {-ADDRESS_FAMILY, -SOCKET_TYPE, -IPPROTO, NONE}, NULL},
	[42 /* def not the answer to life and universe ... */] = {"connect", INT, {-SIGNED_INT, -SOCKADDR_STRUCT, -INT, NONE}, NULL},
	[43] = {"accept", INT, {-INT, SOCKADDR_STRUCT, PTR, NONE}, NULL},
	[44] = {"sendto", INT, {-INT, -MEMSEG, -INT, -SEND_FLAGS, -SOCKADDR_STRUCT, -INT}, NULL},
	[45] = {"recvfrom", INT, {-INT, MEMSEG, INT, SEND_FLAGS, SOCKADDR_STRUCT, INT_PTR}, NULL},
	[46] = {"sendmsg", INT, {-INT, -MSGHDR_STRUCT, -SEND_FLAGS, NONE}, NULL},
	[47] = {"recvmsg", INT, {-INT, MSGHDR_STRUCT, SEND_FLAGS, NONE}, NULL},
	[48] = {"shutdown", INT, {-INT, -SHUTDOWN_HOW, -NONE}, NULL},
	[49] = {"bind", INT, {-INT, -SOCKADDR_STRUCT, -INT}, NULL},
	[50] = {"listen", INT, {-INT, -INT, NONE}, NULL},
	[51] = {"getsockname", INT, {-INT, SOCKADDR_STRUCT, INT_PTR, NONE}, NULL},
	[52] = {"getpeername", INT, {-INT, SOCKADDR_STRUCT, INT_PTR, NONE}, NULL},
	[53] = {"socketpair", INT, {-ADDRESS_FAMILY, -SOCKET_TYPE, -IPPROTO, -PIPEFDS, NONE}, NULL},
	[54] = {"setsockopt", INT, {-INT, -INT, -INT, -MEMSEG, -INT, NONE}, NULL},
	[55] = {"setsockopt", INT, {-INT, -INT, -INT, MEMSEG, INT_PTR, NONE}, NULL},
	[56] = {"clone", INT, {NONE}, custom_handler_clone},
	[57] = {"fork", INT, {NONE}, NULL},
	[58] = {"vfork", INT, {NONE}, NULL},
	[59] = {"execve", INT, {-STRING, -ARGV, -ENVP, NONE}, NULL},
	[60] = {"exit", INT, {-INT, NONE}, NULL},
	[61] = {"wait4", INT, {-SIGNED_INT, WAIT_STATUS, WAIT_OPTIONS, RUSAGE_STRUCT}, NULL},
	[62] = {"kill", INT, {-INT, -SIGNAL_NAME}, NULL},
	[63] = {"uname", INT, {UTSNAME_STRUCT, NONE}, NULL},
	[64] = {"semget", INT, {-HEX, -INT, -IPCS_FLAGS, NONE}, NULL},
	[65] = {"semop", INT, {-INT, -SEMBUF_STRUCT, -INT, NONE}, NULL},
	[66] = {"semctl", INT, {-INT, -INT, -SEMCTL_CMD, -HEX, NONE}, NULL},
	[67] = {"shmdt", INT, {-PTR, NONE}, NULL},
	[68] = {"msgget", INT, {-HEX, -IPCS_FLAGS, NONE}, NULL},
	[69] = {"msgsnd", INT, {-INT, -MSGBUF_STRUCT, -INT, -MSGFLG, NONE}, NULL},
	[70] = {"msgrcv", INT, {-INT, MSGBUF_STRUCT, INT, INT, MSGFLG, NONE}, NULL},
	[71] = {"msgctl", INT, {-INT, -MSGCTL_CMD, MSQID_DS_STRUCT, NONE}, NULL},
	[72] = {"fcntl", INT, {-INT, -FCNTL_CMD, -HEX, NONE}, NULL},
	[73] = {"flock", INT, {-INT, -FLOCK_CMD, NONE}, NULL},
	[74] = {"fsync", INT, {-INT, NONE}, NULL},
	[75] = {"fdatasync", INT, {-INT, NONE}, NULL},
	[76] = {"truncate", INT, {-STRING, -INT, NONE}, NULL},
	[77] = {"ftruncate", INT, {-INT, -INT, NONE}, NULL},
	[78] = {"getdents", INT, {-INT, PTR, INT, NONE}, NULL},
	[79] = {"getcwd", INT, {STRING, INT, NONE}, NULL},
	[80] = {"chdir", INT, {-STRING, NONE}, NULL},
	[81] = {"fchdir", INT, {-INT, NONE}, NULL},
	[82] = {"rename", INT, {-STRING, -STRING, NONE}, NULL},
	[83] = {"mkdir", INT, {-STRING, -OPEN_MODE, NONE}, NULL},
	[84] = {"rmdir", INT, {-STRING, NONE}, NULL},
	[85] = {"creat", INT, {-STRING, -OPEN_MODE, NONE}, NULL},
	[86] = {"link", INT, {-STRING, -STRING, NONE}, NULL},
	[87] = {"unlink", INT, {-STRING, NONE}, NULL},
	[88] = {"symlink", INT, {-STRING, -STRING, NONE}, NULL},
	[89] = {"readlink", INT, {-STRING, MEMSEG, INT, NONE}, NULL},
	[90] = {"chmod", INT, {-STRING, -OPEN_MODE, NONE}, NULL},
	[91] = {"fchmod", INT, {-INT, -OPEN_MODE, NONE}, NULL},
	[92] = {"chown", INT, {-STRING, -INT, -INT, NONE}, NULL},
	[93] = {"fchown", INT, {-INT, -INT, -INT, NONE}, NULL},
	[94] = {"lchown", INT, {-STRING, -INT, -INT, NONE}, NULL},
	[95] = {"umask", INT, {-OPEN_MODE, NONE}, NULL},
	[96] = {"gettimeofday", INT, {TIMEVAL_STRUCT, TIMEZONE_STRUCT, NONE}, NULL},
	[97] = {"getrlimit", INT, {-RLIMIT_RESOURCE, RLIMIT_STRUCT, NONE}, NULL},
	[98] = {"getrusage", INT, {-RUSAGE_WHO, RUSAGE_STRUCT, NONE}, NULL},
	[99] = {"sysinfo", INT, {SYSINFO_STRUCT, NONE}, NULL},
	[100] = {"times", INT, {TMS_STRUCT, NONE}, NULL},
	[101] = {"ptrace", INT, {-PTRACE_REQUEST, -INT, -PTR, -HEX, NONE}, NULL},
	[102] = {"getuid", INT, {NONE}, NULL},
	[103] = {"syslog", INT, {-SYSLOG_TYPE, -MEMSEG, -INT, NONE}, NULL},
	[104] = {"getgid", INT, {NONE}, NULL},
	[105] = {"setuid", INT, {-INT, NONE}, NULL},
	[106] = {"setgid", INT, {-INT, NONE}, NULL},
	[107] = {"geteuid", INT, {NONE}, NULL},
	[108] = {"getegid", INT, {NONE}, NULL},
	[109] = {"setpgid", INT, {-INT, -INT, NONE}, NULL},
	[110] = {"getppid", INT, {NONE}, NULL},
	[111] = {"getpgrp", INT, {NONE}, NULL},
	[112] = {"setsid", INT, {NONE}, NULL},
	[113] = {"setreuid", INT, {-INT, -INT, NONE}, NULL},
	[114] = {"setregid", INT, {-INT, -INT, NONE}, NULL},
	[115] = {"getgroups", INT, {-INT, INT_ARRAY, NONE}, NULL},
	[116] = {"setgroups", INT, {-INT, -INT_ARRAY, NONE}, NULL},
	[117] = {"setresuid", INT, {-INT, -INT, -INT, NONE}, NULL},
	[118] = {"getresuid", INT, {INT_PTR, INT_PTR, INT_PTR, NONE}, NULL},
	[119] = {"setresgid", INT, {-INT, -INT, -INT, NONE}, NULL},
	[120] = {"getresgid", INT, {INT_PTR, INT_PTR, INT_PTR, NONE}, NULL},
	[121] = {"getpgid", INT, {-INT, NONE}, NULL},
	[122] = {"setfsuid", INT, {-INT, NONE}, NULL},
	[123] = {"setfsgid", INT, {-INT, NONE}, NULL},
	[124] = {"getsid", INT, {-INT, NONE}, NULL},
	[125] = {"capget", INT, {-PTR, -PTR, NONE}, NULL},
	[126] = {"capset", INT, {-PTR, -PTR, NONE}, NULL},
	[127] = {"rt_sigpending", INT, {SIGSET_STRUCT, INT, NONE}, NULL},
	[128] = {"rt_sigtimedwait", INT, {-SIGSET_STRUCT, SIGINFO, KERNEL_TIMESPEC_STRUCT, INT, NONE}, NULL},
	[129] = {"rt_sigqueueinfo", INT, {-INT, -SIGNAL_NAME, SIGINFO, NONE}, NULL},
	[130] = {"rt_sigsuspend", INT, {-SIGSET_STRUCT, -INT, NONE}, NULL},
	[131] = {"sigaltstack", INT, {-SIGALTSTACK_STRUCT, SIGALTSTACK_STRUCT, NONE}, NULL},
	[132] = {"utime", INT, {-STRING, UTIMBUF_STRUCT, NONE}, NULL},
	[133] = {"mknod", INT, {-STRING, -OPEN_MODE, -INT, NONE}, NULL},
	[134] = {"uselib", INT, {-STRING, NONE}, NULL},
	[135] = {"personality", INT, {-PERSONALITY_FLAGS, NONE}, NULL},
	[136] = {"ustat", INT, {-INT, USTAT_STRUCT, NONE}, NULL},
	[137] = {"statfs", INT, {-STRING, STAT_STRUCT, NONE}, NULL},
	[138] = {"fstatfs", INT, {-INT, STAT_STRUCT, NONE}, NULL},
	[139] = {"sysfs", INT, {-INT, -HEX, -HEX, NONE}, NULL},
	[140] = {"getpriority", INT, {-PRIORITY_WHICH, -INT, NONE}, NULL},
	[141] = {"setpriority", INT, {-PRIORITY_WHICH, -INT, -INT, NONE}, NULL},
	[142] = {"sched_setparam", INT, {-INT, -SCHED_PARAM_STRUCT, NONE}, NULL},
	[143] = {"sched_getparam", INT, {-INT, SCHED_PARAM_STRUCT, NONE}, NULL},
	[144] = {"sched_setscheduler",
			 INT,
			 {-INT, -SCHED_SETCHEDULER_POLICY, -SCHED_PARAM_STRUCT, NONE}, NULL},
	[145] = {"sched_getscheduler", INT, {-INT, NONE}, NULL},
	[146] = {"sched_get_priority_max", INT, {-SCHED_SETCHEDULER_POLICY, NONE}, NULL},
	[147] = {"sched_get_priority_min", INT, {-SCHED_SETCHEDULER_POLICY, NONE}, NULL},
	[148] = {"sched_rr_get_interval", INT, {-INT, KERNEL_TIMESPEC_STRUCT, NONE}, NULL},
	[149] = {"mlock", INT, {-PTR, -SIGNED_INT, NONE}, NULL},
	[150] = {"munlock", INT, {-PTR, -SIGNED_INT, NONE}, NULL},
	[151] = {"mlockall", INT, {-MLOCKALL_FLAGS, NONE}, NULL},
	[152] = {"munlockall", INT, {NONE}, NULL},
	[153] = {"vhangup", INT, {NONE}, NULL},
	[154] = {"modify_ldt", INT, {-INT, -PTR, -SIGNED_INT, NONE}, NULL},
	[155] = {"pivot_root", INT, {-STRING, -STRING, NONE}, NULL},
	[156] = {"_sysctl", INT, {-PTR, NONE}, NULL},
	[157] = {"prctl", INT, {-PRCTL_OPTION, -HEX, -HEX, -HEX, -HEX, NONE}, NULL},
	[158] = {"arch_prctl", INT, {-PRCTL_OPTION, -HEX, NONE}, NULL},
	[159] = {"adjtimex", INT, {KERNEL_TIMEX_STRUCT, NONE}, NULL},
	[160] = {"setrlimit", INT, {-RLIMIT_RESOURCE, -RLIMIT_STRUCT, NONE}, NULL},
	[161] = {"chroot", INT, {-STRING, NONE}, NULL},
	[162] = {"sync", NONE, {NONE}, NULL},
	[163] = {"acct", INT, {-STRING, NONE}, NULL},
	[164] = {"settimeofday", INT, {-TIMEVAL_STRUCT, -TIMEZONE_STRUCT, NONE}, NULL},
	[165] = {"mount", INT, {-STRING, -STRING, -STRING, -MOUNT_FLAGS, -STRING, NONE}, NULL},
	[166] = {"umount2", INT, {-STRING, -MOUNT_FLAGS, NONE}, NULL},
	[167] = {"swapon", INT, {-STRING, -SWAP_FLAGS, NONE}, NULL},
	[168] = {"swapoff", INT, {-STRING, NONE}, NULL},
	[169] = {"reboot", INT, {-HEX, -HEX, -INT, -PTR, NONE}, NULL},
	[170] = {"sethostname", INT, {-MEMSEG, -INT}, NULL},
	[171] = {"setdomainname", INT, {-MEMSEG, -INT}, NULL},
	[172] = {"iopl", INT, {-INT, NONE}, NULL},
	[173] = {"ioperm", INT, {-HEX, -HEX, -INT, NONE}, NULL},
	[174] = {"create_module", INT, {-STRING, -INT, NONE}, NULL},
	[175] = {"init_module", INT, {-PTR, -INT, -STRING, NONE}, NULL},
	[176] = {"delete_module", INT, {-STRING, -INT, NONE}, NULL},
	[177] = {"get_kernel_syms", INT, {-PTR, NONE}, NULL},
	[178] = {"query_module", INT, {-STRING, -INT, -PTR, -INT, -PTR, NONE}, NULL},
	[179] = {"quotactl", INT, {-INT, -STRING, -INT, -PTR, NONE}, NULL},
	[180] = {"nfsservctl", INT, {-INT, -PTR, -PTR, NONE}, NULL},
	[181] = {"getpmsg", INT, {-INT, -PTR, -PTR, -INT, NONE}, NULL},
	[182] = {"putpmsg", INT, {-INT, -PTR, -PTR, -INT, NONE}, NULL},
	[183] = {"afs_syscall", INT, {NONE}, NULL},
	[184] = {"tuxcall", INT, {NONE}, NULL},
	[185] = {"security", INT, {NONE}, NULL},
	[186] = {"gettid", INT, {NONE}, NULL},
	[187] = {"readahead", INT, {-INT, -INT, NONE}, NULL},
	[188] = {"setxattr", INT, {-STRING, -STRING, -PTR, -INT, -INT, NONE}, NULL},
	[189] = {"lsetxattr", INT, {-STRING, -STRING, -PTR, -INT, -INT, NONE}, NULL},
	[190] = {"fsetxattr", INT, {-INT, -STRING, -PTR, -INT, -INT, NONE}, NULL},
	[191] = {"getxattr", INT, {-STRING, -STRING, -PTR, -INT, NONE}, NULL},
	[192] = {"lgetxattr", INT, {-STRING, -STRING, -PTR, -INT, NONE}, NULL},
	[193] = {"fgetxattr", INT, {-INT, -STRING, -PTR, -INT, NONE}, NULL},
	[194] = {"listxattr", INT, {-STRING, -STRING, -INT, NONE}, NULL},
	[195] = {"llistxattr", INT, {-STRING, -STRING, -INT, NONE}, NULL},
	[196] = {"flistxattr", INT, {-INT, -STRING, -INT, NONE}, NULL},
	[197] = {"removexattr", INT, {-STRING, -STRING, NONE}, NULL},
	[198] = {"lremovexattr", INT, {-STRING, -STRING, NONE}, NULL},
	[199] = {"fremovexattr", INT, {-INT, -STRING, NONE}, NULL},
	[200] = {"tkill", INT, {-INT, -SIGNAL_NAME, NONE}, NULL},
	[201] = {"time", INT, {TIME_T, NONE}, NULL},
	[202] = {"futex", INT, {INT_PTR, INT, INT, KERNEL_TIMESPEC_STRUCT, INT_PTR, INT}, NULL},
	[203] = {"sched_setaffinity", INT, {-INT, -INT, -INT_PTR, NONE}, NULL},
	[204] = {"sched_getaffinity", INT, {-INT, -INT, -INT_PTR, NONE}, NULL},
	[205] = {"set_thread_area", INT, {-PTR, NONE}, NULL},
	[206] = {"io_setup", INT, {-INT, INT_PTR, NONE}, NULL},
	[207] = {"io_destroy", INT, {-INT, NONE}, NULL},
	[208] = {"io_getevents",
			 INT,
			 {-INT, -INT, -INT, IO_EVENT_STRUCT, KERNEL_TIMESPEC_STRUCT, NONE}, NULL},
	[209] = {"io_submit", INT, {-INT, -INT, -PTR, NONE}, NULL},
	[210] = {"io_cancel", INT, {-INT, -PTR, -PTR, NONE}, NULL},
	[211] = {"get_thread_area", INT, {PTR, NONE}, NULL},
	[212] = {"lookup_dcookie", INT, {INT, -MEMSEG, -INT, NONE}, NULL},
	[213] = {"epoll_create", INT, {-INT, NONE}, NULL},
	[214] = {"epoll_ctl_old", INT, {-INT, -EPOLL_CTL_CMD, -EPOLL_EVENT_STRUCT, NONE}, NULL},
	[215] = {"epoll_wait_old", INT, {-INT, EPOLL_EVENT_STRUCT_ARRAY, INT, NONE}, NULL},
	[216] = {"remap_file_pages", INT, {-INT, -INT, -HEX, -INT, -HEX, NONE}, NULL},
	[217] = {"getdents64", INT, {-INT, -PTR, -INT, NONE}, NULL},
	[218] = {"set_tid_address", INT, {-PTR, NONE}, NULL},
	[219] = {"restart_syscall", INT, {NONE}, NULL},
	[220] = {"semtimedop", INT, {-INT, -SEMBUF_STRUCT, -INT, KERNEL_TIMESPEC_STRUCT, NONE}, NULL},
	[221] = {"fadvise64", INT, {-INT, -INT, -INT, -ADVISE, NONE}, NULL},
	[222] = {"timer_create", INT, {-CLOCKID_T, -SIGEVENT_STRUCT, -INT_PTR, NONE}, NULL},
	[223] = {"timer_settime",
			 INT,
			 {-INT, -TIMER_SETTIME_FLAGS, -KERNEL_ITIMERSPEC_STRUCT, KERNEL_ITIMERSPEC_STRUCT,
			  NONE}, NULL},
	[224] = {"timer_gettime", INT, {-INT, KERNEL_ITIMERSPEC_STRUCT, NONE}, NULL},
	[225] = {"timer_getoverrun", INT, {-INT, NONE}, NULL},
	[226] = {"timer_delete", INT, {-INT, NONE}, NULL},
	[227] = {"clock_settime", INT, {-CLOCKID_T, -KERNEL_TIMESPEC_STRUCT, NONE}, NULL},
	[228] = {"clock_gettime", INT, {-CLOCKID_T, KERNEL_TIMESPEC_STRUCT, NONE}, NULL},
	[229] = {"clock_getres", INT, {-CLOCKID_T, KERNEL_TIMESPEC_STRUCT, NONE}, NULL},
	[230] = {"clock_nanosleep",
			 INT,
			 {-CLOCKID_T, -INT, -KERNEL_TIMESPEC_STRUCT, -KERNEL_TIMESPEC_STRUCT, NONE}, NULL},
	[231] = {"exit_group", INT, {-INT, NONE}, NULL},
	[232] = {"epoll_wait", INT, {-INT, EPOLL_EVENT_STRUCT_ARRAY, INT, INT, NONE}, NULL},
	[233] = {"epoll_ctl", INT, {-INT, -EPOLL_CTL_CMD, -INT, -EPOLL_EVENT_STRUCT, NONE}, NULL},
	[234] = {"tgkill", INT, {-INT, -INT, -SIGNAL_NAME, NONE}, NULL},
	[235] = {"utimes", INT, {-STRING, TIMEVAL_STRUCT}, NULL},
	[236] = {"vserver", INT, {NONE}, NULL},
	[237] = {"mbind", INT, {-INT, -INT, -INT, -INT_PTR, -INT, -HEX}, NULL},
	[238] = {"set_mempolicy", INT, {-INT, -INT_PTR, -INT, NONE}, NULL},
	[239] = {"get_mempolicy", INT, {-INT_PTR, -INT_PTR, -INT, -INT_PTR, -INT, NONE}, NULL},
	[240] = {"mq_open", INT, {-STRING, -OPEN_FLAGS, -OPEN_MODE, -MQ_ATTR_STRUCT, NONE}, NULL},
	[241] = {"mq_unlink", INT, {-STRING, NONE}, NULL},
	[242] = {"mq_timedsend", INT, {-INT, -MEMSEG, -INT, -INT, -KERNEL_TIMESPEC_STRUCT, NONE}, NULL},
	[243] = {"mq_timedreceive", INT, {-INT, MEMSEG, INT, INT_PTR, KERNEL_TIMESPEC_STRUCT, NONE}, NULL},
	[244] = {"mq_notify", INT, {-INT, SIGEVENT_STRUCT, NONE}, NULL},
	[245] = {"mq_getsetattr", INT, {-INT, -MQ_ATTR_STRUCT, -MQ_ATTR_STRUCT, NONE}, NULL},
	[246] = {"kexec_load", INT, {-INT, -INT, -PTR, -INT, NONE}, NULL},
	[247] = {"waitid", INT, {-INT, -INT, SIGINFO, WAITID_WHICH, WAIT_OPTIONS, RUSAGE_STRUCT}, NULL},
	[248] = {"add_key", INT, {-STRING, -STRING, -PTR, -INT, -INT, NONE}, NULL},
	[249] = {"request_key", INT, {-STRING, -STRING, -STRING, -INT, NONE}, NULL},
	[250] = {"keyctl", INT, {-KEYCTL_CMD, -HEX, -HEX, -HEX, -HEX, NONE}, NULL},
	[251] = {"ioprio_set", INT, {-IOPRIO_WHICH, -INT, -HEX, NONE}, NULL},
	[252] = {"ioprio_get", INT, {-IOPRIO_WHICH, -INT, NONE}, NULL},
	[253] = {"inotify_init", INT, {NONE}, NULL},
	[254] = {"inotify_add_watch", INT, {-INT, -STRING, -HEX, NONE}, NULL},
	[255] = {"inotify_rm_watch", INT, {-INT, -SIGNED_INT, NONE}, NULL},
	[256] = {"migrate_pages", INT, {-INT, -INT, -PTR, -PTR, NONE}, NULL},
	[257] = {"openat", INT, {-OPENAT_DIRFD, -STRING, -OPEN_FLAGS, NONE}, NULL},
	[258] = {"mkdirat", INT, {-OPENAT_DIRFD, -STRING, -OPEN_FLAGS, -OPEN_MODE, NONE}, NULL},
	[259] = {"mknodat", INT, {-OPENAT_DIRFD, -STRING, -OPEN_FLAGS, -OPEN_MODE, -INT, NONE}, NULL},
	[260] = {"fchownat", INT, {-OPENAT_DIRFD, -STRING, -INT, -INT, -INT, NONE}, NULL},
	[261] = {"futimesat", INT, {-OPENAT_DIRFD, -STRING, TIMEVAL_STRUCT, NONE}, NULL},
	[262] = {"newfstatat", INT, {-OPENAT_DIRFD, -STRING, STAT_STRUCT, NEWFSTATAT_FLAGS, NONE}, NULL},
	[263] = {"unlinkat", INT, {-OPENAT_DIRFD, -STRING, -INT, NONE}, NULL},
	[264] = {"renameat", INT, {-OPENAT_DIRFD, -STRING, -OPENAT_DIRFD, -STRING, NONE}, NULL},
	[265] = {"linkat", INT, {-OPENAT_DIRFD, -STRING, -OPENAT_DIRFD, -STRING, -INT, NONE}, NULL},
	[266] = {"symlinkat", INT, {-STRING, -OPENAT_DIRFD, -STRING, NONE}, NULL},
	[267] = {"readlinkat", INT, {-OPENAT_DIRFD, -STRING, MEMSEG, INT, NONE}, NULL},
	[268] = {"fchmodat", INT, {-OPENAT_DIRFD, -STRING, -OPEN_MODE, NONE}, NULL},
	[269] = {"faccessat", INT, {-OPENAT_DIRFD, -STRING, -ACCESS_MODE, NONE}, NULL},
	[270] = {"pselect6",
			 INT,
			 {-INT, -FD_SET_STRUCT, -FD_SET_STRUCT, -FD_SET_STRUCT, -KERNEL_TIMESPEC_STRUCT,
			  -INT_PTR}, NULL},
	[271] = {"ppoll",
			 INT,
			 {-FD_SET_STRUCT, -INT, -KERNEL_TIMESPEC_STRUCT, -SIGSET_STRUCT, -INT, NONE}, NULL},
	[272] = {"unshare", INT, {-INT, NONE}, NULL},
	[273] = {"set_robust_list", INT, {-PTR, -INT, NONE}, NULL},
	[274] = {"get_robust_list", INT, {-INT, -PTR, -INT_PTR, NONE}, NULL},
	[275] = {"splice", INT, {-INT, -PTR, -INT, -PTR, -INT, -HEX}, NULL},
	[276] = {"tee", INT, {-INT, -INT, -INT, -HEX, NONE}, NULL},
	[277] = {"sync_file_range", INT, {-INT, -INT, -INT, -HEX, NONE}, NULL},
	[278] = {"vmsplice", INT, {-INT, -PTR, -INT, -HEX, NONE}, NULL},
	[279] = {"move_pages", INT, {-INT, -INT, -PTR, -PTR, -INT_PTR, -INT}, NULL},
	[280] = {"utimensat", INT, {-OPENAT_DIRFD, -STRING, TIMEVAL_STRUCT, -INT, NONE}, NULL},
	[281] = {"epoll_pwait",
			 INT,
			 {-INT, EPOLL_EVENT_STRUCT_ARRAY, INT, INT, SIGSET_STRUCT, NONE}, NULL},
	[282] = {"signalfd", INT, {-INT, -SIGSET_STRUCT, -INT, NONE}, NULL},
	[283] = {"timerfd_create", INT, {-CLOCKID_T, -INT, NONE}, NULL},
	[284] = {"eventfd", INT, {-INT, NONE}, NULL},
	[285] = {"fallocate", INT, {-INT, -INT, -INT, -INT, NONE}, NULL},
	[286] = {"timerfd_settime", INT, {-INT, -TIMER_SETTIME_FLAGS, -KERNEL_ITIMERSPEC_STRUCT, -KERNEL_ITIMERSPEC_STRUCT, NONE}, NULL},
	[287] = {"timerfd_gettime", INT, {-INT, -KERNEL_ITIMERSPEC_STRUCT, NONE}, NULL},
	[288] = {"accept4", INT, {-INT, SOCKADDR_STRUCT, INT_PTR, -INT, NONE}, NULL},
	[289] = {"signalfd4",
			 INT,
			 {-INT, -SIGSET_STRUCT, -INT, -SIGNED_INT, NONE}, NULL},
	[290] = {"eventfd2", INT, {-INT, -INT, NONE}, NULL},
	[291] = {"epoll_create1", INT, {-INT, NONE}, NULL},
	[292] = {"dup3", INT, {-INT, -INT, -OPEN_FLAGS, NONE}, NULL},
	[293] = {"pipe2", INT, {PIPEFDS, -OPEN_FLAGS, NONE}, NULL},
	[294] = {"inotify_init1", INT, {-INT, NONE}, NULL},
	[295] = {"preadv", INT, {-INT, IOVEC_STRUCT, INT, INT, NONE}, NULL},
	[296] = {"pwritev", INT, {-INT, -IOVEC_STRUCT, -INT, -INT, NONE}, NULL},
	[297] = {"rt_tgsigqueueinfo", INT, {-INT, -INT, -SIGNAL_NAME, -SIGINFO, NONE}, NULL},
	[298] = {"perf_event_open", INT, {-PTR, -INT, -INT, -INT, -HEX, NONE}, NULL},	
	[299] = {"recvmmsg", INT, {-INT, -PTR, -INT, -HEX, KERNEL_TIMESPEC_STRUCT, NONE}, NULL},
	[300] = {"fanotify_init", INT, {-INT, -INT, NONE}, NULL},
	[301] = {"fanotify_mark", INT, {-INT, -INT, -HEX, -INT, -STRING, NONE}, NULL},
	[302] = {"prlimit64", INT, {-INT, -PRLIMIT_RESOURCE, -RLIMIT64_STRUCT, RLIMIT64_STRUCT, NONE}, NULL},
	[303] = {"name_to_handle_at", INT, {-OPENAT_DIRFD, -STRING, -PTR, INT_PTR, INT}, NULL},
	[304] = {"open_by_handle_at", INT, {-INT, -PTR, INT, NONE}, NULL},
	[305] = {"clock_adjtime", INT, {-CLOCKID_T, -KERNEL_TIMEX_STRUCT, NONE}, NULL},
	[306] = {"syncfs", INT, {-INT, NONE}, NULL},
	[307] = {"sendmmsg", INT, {-INT, -MSGHDR_STRUCT, -INT, -HEX, SEND_FLAGS}, NULL},
	[308] = {"setns", INT, {-INT, -INT}, NULL},
	[309] = {"getcpu", INT, {-INT_PTR, -INT_PTR, -PTR, NONE}, NULL},
	[310] = {"process_vm_readv", INT, {-INT, -IOVEC_STRUCT, -INT, -IOVEC_STRUCT, -INT, -INT}, NULL},
	[311] = {"process_vm_writev", INT, {-INT, -IOVEC_STRUCT, -INT, -IOVEC_STRUCT, -INT, -INT}, NULL},
	[312] = {"kcmp", INT, {-INT, -INT, -INT, -INT, -INT, NONE}, NULL},
	[313] = {"finit_module", INT, {-INT, -STRING, -INT, NONE}, NULL},
	[314] = {"sched_setattr", INT, {-INT, -PTR, -INT, NONE}, NULL},
	[315] = {"sched_getattr", INT, {-INT, -PTR, -INT, -INT, NONE}, NULL},
	[316] = {"renameat2", INT, {-INT, -STRING, -INT, -STRING, -INT, NONE}, NULL},
	[317] = {"seccomp", INT, {-INT, -INT, -PTR, NONE}, NULL},
	[318] = {"getrandom", INT, {-PTR, -INT, -INT, NONE}, NULL},
	[319] = {"memfd_create", INT, {-STRING, -INT, NONE}, NULL},
	[320] = {"kexec_file_load", INT, {-INT, -INT, -INT, -STRING, -INT, NONE}, NULL},
	[321] = {"bpf", INT, {-INT, -PTR, -INT, NONE}, NULL},
	[322] = {"execveat", INT, {-OPENAT_DIRFD, -STRING, -ARGV, -ENVP, -INT, NONE}, NULL},
	[323] = {"userfaultfd", INT, {-INT, NONE}, NULL},
	[324] = {"membarrier", INT, {-INT, -INT, NONE}, NULL},
	[325] = {"mlock2", INT, {-PTR, -INT, -INT, NONE}, NULL},
	[326] = {"copy_file_range", INT, {-INT, -INT_PTR, -INT, -INT_PTR, -INT, NONE}, NULL},
	[327] = {"preadv2", INT, {-INT, -IOVEC_STRUCT, -INT, -INT, -INT, NONE}, NULL},
	[328] = {"pwritev2", INT, {-INT, -IOVEC_STRUCT, -INT, -INT, -INT, NONE}, NULL},
	[329] = {"pkey_mprotect", INT, {-PTR, -INT, -INT, -INT, NONE}, NULL},
	[330] = {"pkey_alloc", INT, {-INT, -INT, NONE}, NULL},
	[331] = {"pkey_free", INT, {-INT, NONE}, NULL},
	[332] = {"statx", INT, {-INT, -STRING, -INT, -HEX, PTR, NONE}, NULL},
	[333] = {"io_pgetevents", INT, {-INT, -INT, -INT, -IO_EVENT_STRUCT, -KERNEL_TIMESPEC_STRUCT, NONE}, NULL},
	[334] = {"rseq", INT, {-PTR, -HEX, -INT, -HEX, NONE}, NULL},
	[424] = {"pidfd_send_signal", INT, {-INT, -SIGNAL_NAME, -SIGINFO, -INT, NONE}, NULL},
	[425] = {"io_uring_setup", INT, {-INT, -PTR, NONE}, NULL},
	[426] = {"io_uring_enter", INT, {-INT, -INT, -INT, -INT, -PTR, -INT}, NULL},
	[427] = {"io_uring_register", INT, {-INT, -INT, -INT, NONE}, NULL},
	[428] = {"open_tree", INT, {-INT, -STRING, -INT, NONE}, NULL},
	[429] = {"move_mount", INT, {-INT, -STRING, -INT, -STRING, -MOUNT_FLAGS, NONE}, NULL},
	[430] = {"fsopen", INT, {-STRING, -INT, NONE}, NULL},
	[431] = {"fsconfig", INT, {-INT, -INT, -INT, NONE}, NULL},
	[432] = {"fsmount", INT, {-INT, -INT, -INT, -INT, NONE}, NULL},
	[433] = {"fspick", INT, {-INT, -INT, -INT, NONE}, NULL},
	[434] = {"pidfd_open", INT, {-INT, -INT, NONE}, NULL},
	[435] = {"clone3", INT, {-INT, -INT, -INT, -INT, -INT, NONE}, NULL},
	[436] = {"close_range", INT, {-INT, -INT, NONE}, NULL},
};