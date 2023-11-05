#pragma once

#include <syscall_strace.h>
#include <param_types.h>

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
	[13] = {"rt_sigaction", INT, {-SIGNAL_NAME, -SIGACTION_STRUCT, SIGACTION_STRUCT, INT, NONE}},
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
	[42 /* def not the answer to life and universe ... */] = {"connect", INT, {-SIGNED_INT, -SOCKADDR_STRUCT, -INT, NONE}},
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
	[101] = {"ptrace", INT, {-PTRACE_REQUEST, -INT, -PTR, -HEX, NONE}},
	[102] = {"getuid", INT, {NONE}},
	[103] = {"syslog", INT, {-SYSLOG_TYPE, -MEMSEG, -INT, NONE}},
	[104] = {"getgid", INT, {NONE}},
	[105] = {"setuid", INT, {-INT, NONE}},
	[106] = {"setgid", INT, {-INT, NONE}},
	[107] = {"geteuid", INT, {NONE}},
	[108] = {"getegid", INT, {NONE}},
	[109] = {"setpgid", INT, {-INT, -INT, NONE}},
	[110] = {"getppid", INT, {NONE}},
	[111] = {"getpgrp", INT, {NONE}},
	[112] = {"setsid", INT, {NONE}},
	[113] = {"setreuid", INT, {-INT, -INT, NONE}},
	[114] = {"setregid", INT, {-INT, -INT, NONE}},
	[115] = {"getgroups", INT, {-INT, INT_ARRAY, NONE}},
	[116] = {"setgroups", INT, {-INT, -INT_ARRAY, NONE}},
	[117] = {"setresuid", INT, {-INT, -INT, -INT, NONE}},
	[118] = {"getresuid", INT, {INT_PTR, INT_PTR, INT_PTR, NONE}},
	[119] = {"setresgid", INT, {-INT, -INT, -INT, NONE}},
	[120] = {"getresgid", INT, {INT_PTR, INT_PTR, INT_PTR, NONE}},
	[121] = {"getpgid", INT, {-INT, NONE}},
	[122] = {"setfsuid", INT, {-INT, NONE}},
	[123] = {"setfsgid", INT, {-INT, NONE}},
	[124] = {"getsid", INT, {-INT, NONE}},
	[125] = {"capget", INT, {-PTR, -PTR, NONE}},
	[126] = {"capset", INT, {-PTR, -PTR, NONE}},
	[127] = {"rt_sigpending", INT, {SIGSET_STRUCT, INT, NONE}},
	[128] = {"rt_sigtimedwait", INT, {-SIGSET_STRUCT, SIGINFO, KERNEL_TIMESPEC_STRUCT, INT, NONE}},
	[129] = {"rt_sigqueueinfo", INT, {-INT, -SIGNAL_NAME, SIGINFO, NONE}},
	[130] = {"rt_sigsuspend", INT, {-SIGSET_STRUCT, -INT, NONE}},
	[131] = {"sigaltstack", INT, {-SIGALTSTACK_STRUCT, SIGALTSTACK_STRUCT, NONE}},
	[132] = {"utime", INT, {-STRING, UTIMBUF_STRUCT, NONE}},
	[133] = {"mknod", INT, {-STRING, -OPEN_MODE, -INT, NONE}},
	[134] = {"uselib", INT, {-STRING, NONE}},
	[135] = {"personality", INT, {-PERSONALITY_FLAGS, NONE}},
	[136] = {"ustat", INT, {-INT, USTAT_STRUCT, NONE}},
	[137] = {"statfs", INT, {-STRING, STAT_STRUCT, NONE}},
	[138] = {"fstatfs", INT, {-INT, STAT_STRUCT, NONE}},
	[139] = {"sysfs", INT, {-INT, -HEX, -HEX, NONE}},
	[140] = {"getpriority", INT, {-PRIORITY_WHICH, -INT, NONE}},
	[141] = {"setpriority", INT, {-PRIORITY_WHICH, -INT, -INT, NONE}},
	[142] = {"sched_setparam", INT, {-INT, -SCHED_PARAM_STRUCT, NONE}},
	[143] = {"sched_getparam", INT, {-INT, SCHED_PARAM_STRUCT, NONE}},
	[144] = {"sched_setscheduler",
			 INT,
			 {-INT, -SCHED_SETCHEDULER_POLICY, -SCHED_PARAM_STRUCT, NONE}},
	[145] = {"sched_getscheduler", INT, {-INT, NONE}},
	[146] = {"sched_get_priority_max", INT, {-SCHED_SETCHEDULER_POLICY, NONE}},
	[147] = {"sched_get_priority_min", INT, {-SCHED_SETCHEDULER_POLICY, NONE}},
	[148] = {"sched_rr_get_interval", INT, {-INT, KERNEL_TIMESPEC_STRUCT, NONE}},
	[149] = {"mlock", INT, {-PTR, -SIGNED_INT, NONE}},
	[150] = {"munlock", INT, {-PTR, -SIGNED_INT, NONE}},
	[151] = {"mlockall", INT, {-MLOCKALL_FLAGS, NONE}},
	[152] = {"munlockall", INT, {NONE}},
	[153] = {"vhangup", INT, {NONE}},
	[154] = {"modify_ldt", INT, {-INT, -PTR, -SIGNED_INT, NONE}},
	[155] = {"pivot_root", INT, {-STRING, -STRING, NONE}},
	[156] = {"_sysctl", INT, {-PTR, NONE}},
	[157] = {"prctl", INT, {-PRCTL_OPTION, -HEX, -HEX, -HEX, -HEX, NONE}},
	[158] = {"arch_prctl", INT, {-PRCTL_OPTION, -HEX, NONE}},
	[159] = {"adjtimex", INT, {KERNEL_TIMEX_STRUCT, NONE}},
	[160] = {"setrlimit", INT, {-RLIMIT_RESOURCE, -RLIMIT_STRUCT, NONE}},
	[161] = {"chroot", INT, {-STRING, NONE}},
	[162] = {"sync", NONE, {NONE}},
	[163] = {"acct", INT, {-STRING, NONE}},
	[164] = {"settimeofday", INT, {-TIMEVAL_STRUCT, -TIMEZONE_STRUCT, NONE}},
	[165] = {"mount", INT, {-STRING, -STRING, -STRING, -MOUNT_FLAGS, -STRING, NONE}},
	[166] = {"umount2", INT, {-STRING, -MOUNT_FLAGS, NONE}},
	[167] = {"swapon", INT, {-STRING, -SWAP_FLAGS, NONE}},
	[168] = {"swapoff", INT, {-STRING, NONE}},
	[169] = {"reboot", INT, {-HEX, -HEX, -INT, -PTR, NONE}},
	[170] = {"sethostname", INT, {-MEMSEG, -INT}},
	[171] = {"setdomainname", INT, {-MEMSEG, -INT}},
	[172] = {"iopl", INT, {-INT, NONE}},
	[173] = {"ioperm", INT, {-HEX, -HEX, -INT, NONE}},
	[174] = {"create_module", INT, {-STRING, -INT, NONE}},
	[175] = {"init_module", INT, {-PTR, -INT, -STRING, NONE}},
	[176] = {"delete_module", INT, {-STRING, -INT, NONE}},
	[177] = {"get_kernel_syms", INT, {-PTR, NONE}},
	[178] = {"query_module", INT, {-STRING, -INT, -PTR, -INT, -PTR, NONE}},
	[179] = {"quotactl", INT, {-INT, -STRING, -INT, -PTR, NONE}},
	[180] = {"nfsservctl", INT, {-INT, -PTR, -PTR, NONE}},
	[181] = {"getpmsg", INT, {-INT, -PTR, -PTR, -INT, NONE}},
	[182] = {"putpmsg", INT, {-INT, -PTR, -PTR, -INT, NONE}},
	[183] = {"afs_syscall", INT, {NONE}},
	[184] = {"tuxcall", INT, {NONE}},
	[185] = {"security", INT, {NONE}},
	[186] = {"gettid", INT, {NONE}},
	[187] = {"readahead", INT, {-INT, -INT, NONE}},
	[188] = {"setxattr", INT, {-STRING, -STRING, -PTR, -INT, -INT, NONE}},
	[189] = {"lsetxattr", INT, {-STRING, -STRING, -PTR, -INT, -INT, NONE}},
	[190] = {"fsetxattr", INT, {-INT, -STRING, -PTR, -INT, -INT, NONE}},
	[191] = {"getxattr", INT, {-STRING, -STRING, -PTR, -INT, NONE}},
	[192] = {"lgetxattr", INT, {-STRING, -STRING, -PTR, -INT, NONE}},
	[193] = {"fgetxattr", INT, {-INT, -STRING, -PTR, -INT, NONE}},
	[194] = {"listxattr", INT, {-STRING, -STRING, -INT, NONE}},
	[195] = {"llistxattr", INT, {-STRING, -STRING, -INT, NONE}},
	[196] = {"flistxattr", INT, {-INT, -STRING, -INT, NONE}},
	[197] = {"removexattr", INT, {-STRING, -STRING, NONE}},
	[198] = {"lremovexattr", INT, {-STRING, -STRING, NONE}},
	[199] = {"fremovexattr", INT, {-INT, -STRING, NONE}},
	[200] = {"tkill", INT, {-INT, -SIGNAL_NAME, NONE}},
	[201] = {"time", INT, {TIME_T, NONE}},
	[202] = {"futex", INT, {INT_PTR, INT, INT, KERNEL_TIMESPEC_STRUCT, INT_PTR, INT}},
	[203] = {"sched_setaffinity", INT, {-INT, -INT, -INT_PTR, NONE}},
	[204] = {"sched_getaffinity", INT, {-INT, -INT, -INT_PTR, NONE}},
	[205] = {"set_thread_area", INT, {-PTR, NONE}},
	[206] = {"io_setup", INT, {-INT, INT_PTR, NONE}},
	[207] = {"io_destroy", INT, {-INT, NONE}},
	[208] = {"io_getevents",
			 INT,
			 {-INT, -INT, -INT, IO_EVENT_STRUCT, KERNEL_TIMESPEC_STRUCT, NONE}},
	[209] = {"io_submit", INT, {-INT, -INT, -PTR, NONE}},
	[210] = {"io_cancel", INT, {-INT, -PTR, -PTR, NONE}},
	[211] = {"get_thread_area", INT, {PTR, NONE}},
	[212] = {"lookup_dcookie", INT, {INT, -MEMSEG, -INT, NONE}},
	[213] = {"epoll_create", INT, {-INT, NONE}},
	[214] = {"epoll_ctl_old", INT, {-INT, -EPOLL_CTL_CMD, -EPOLL_EVENT_STRUCT, NONE}},
	[215] = {"epoll_wait_old", INT, {-INT, EPOLL_EVENT_STRUCT_ARRAY, INT, NONE}},
	[216] = {"remap_file_pages", INT, {-INT, -INT, -HEX, -INT, -HEX, NONE}},
	[217] = {"getdents64", INT, {-INT, -PTR, -INT, NONE}},
	[218] = {"set_tid_address", INT, {-PTR, NONE}},
	[219] = {"restart_syscall", INT, {NONE}},
	[220] = {"semtimedop", INT, {-INT, -SEMBUF_STRUCT, -INT, KERNEL_TIMESPEC_STRUCT, NONE}},
	[221] = {"fadvise64", INT, {-INT, -INT, -INT, -ADVISE, NONE}},
	[222] = {"timer_create", INT, {-CLOCKID_T, -SIGEVENT_STRUCT, -INT_PTR, NONE}},
	[223] = {"timer_settime",
			 INT,
			 {-INT, -TIMER_SETTIME_FLAGS, -KERNEL_ITIMERSPEC_STRUCT, KERNEL_ITIMERSPEC_STRUCT,
			  NONE}},
	[224] = {"timer_gettime", INT, {-INT, KERNEL_ITIMERSPEC_STRUCT, NONE}},
	[225] = {"timer_getoverrun", INT, {-INT, NONE}},
	[226] = {"timer_delete", INT, {-INT, NONE}},
	[227] = {"clock_settime", INT, {-CLOCKID_T, -KERNEL_TIMESPEC_STRUCT, NONE}},
	[228] = {"clock_gettime", INT, {-CLOCKID_T, KERNEL_TIMESPEC_STRUCT, NONE}},
	[229] = {"clock_getres", INT, {-CLOCKID_T, KERNEL_TIMESPEC_STRUCT, NONE}},
	[230] = {"clock_nanosleep",
			 INT,
			 {-CLOCKID_T, -INT, -KERNEL_TIMESPEC_STRUCT, -KERNEL_TIMESPEC_STRUCT, NONE}},
	[231] = {"exit_group", INT, {-INT, NONE}},
	[232] = {"epoll_wait", INT, {-INT, EPOLL_EVENT_STRUCT_ARRAY, INT, INT, NONE}},
	[233] = {"epoll_ctl", INT, {-INT, -EPOLL_CTL_CMD, -INT, -EPOLL_EVENT_STRUCT, NONE}},
	[234] = {"tgkill", INT, {-INT, -INT, -SIGNAL_NAME, NONE}},
	[235] = {"utimes", INT, {-STRING, TIMEVAL_STRUCT}},
	[236] = {"vserver", INT, {NONE}},
	[237] = {"mbind", INT, {-INT, -INT, -INT, -INT_PTR, -INT, -HEX}},
	[238] = {"set_mempolicy", INT, {-INT, -INT_PTR, -INT, NONE}},
	[239] = {"get_mempolicy", INT, {-INT_PTR, -INT_PTR, -INT, -INT_PTR, -INT, NONE}},
	[240] = {"mq_open", INT, {-STRING, -OPEN_FLAGS, -OPEN_MODE, -MQ_ATTR_STRUCT, NONE}},
	[241] = {"mq_unlink", INT, {-STRING, NONE}},
	[242] = {"mq_timedsend", INT, {-INT, -MEMSEG, -INT, -INT, -KERNEL_TIMESPEC_STRUCT, NONE}},
	[243] = {"mq_timedreceive", INT, {-INT, MEMSEG, INT, INT_PTR, KERNEL_TIMESPEC_STRUCT, NONE}},
	[244] = {"mq_notify", INT, {-INT, SIGEVENT_STRUCT, NONE}},
	[245] = {"mq_getsetattr", INT, {-INT, -MQ_ATTR_STRUCT, -MQ_ATTR_STRUCT, NONE}},
	[246] = {"kexec_load", INT, {-INT, -INT, -PTR, -INT, NONE}},
	[247] = {"waitid", INT, {-INT, -INT, SIGINFO, WAITID_WHICH, WAIT_OPTIONS, RUSAGE_STRUCT}},
	[248] = {"add_key", INT, {-STRING, -STRING, -PTR, -INT, -INT, NONE}},
	[249] = {"request_key", INT, {-STRING, -STRING, -STRING, -INT, NONE}},
	[250] = {"keyctl", INT, {-KEYCTL_CMD, -HEX, -HEX, -HEX, -HEX, NONE}},
	[251] = {"ioprio_set", INT, {-IOPRIO_WHICH, -INT, -HEX, NONE}},
	[252] = {"ioprio_get", INT, {-IOPRIO_WHICH, -INT, NONE}},
	[253] = {"inotify_init", INT, {NONE}},
	[254] = {"inotify_add_watch", INT, {-INT, -STRING, -HEX, NONE}},
	[255] = {"inotify_rm_watch", INT, {-INT, -SIGNED_INT, NONE}},
	[256] = {"migrate_pages", INT, {-INT, -INT, -PTR, -PTR, NONE}},
	[257] = {"openat", INT, {-OPENAT_DIRFD, -STRING, -OPEN_FLAGS, NONE}},
	[258] = {"mkdirat", INT, {-OPENAT_DIRFD, -STRING, -OPEN_FLAGS, -OPEN_MODE, NONE}},
	[259] = {"mknodat", INT, {-OPENAT_DIRFD, -STRING, -OPEN_FLAGS, -OPEN_MODE, -INT, NONE}},
	[260] = {"fchownat", INT, {-OPENAT_DIRFD, -STRING, -INT, -INT, -INT, NONE}},
	[261] = {"futimesat", INT, {-OPENAT_DIRFD, -STRING, TIMEVAL_STRUCT, NONE}},
	[262] = {"newfstatat", INT, {-OPENAT_DIRFD, -STRING, STAT_STRUCT, NEWFSTATAT_FLAGS, NONE}},
	[263] = {"unlinkat", INT, {-OPENAT_DIRFD, -STRING, -INT, NONE}},
	[264] = {"renameat", INT, {-OPENAT_DIRFD, -STRING, -OPENAT_DIRFD, -STRING, NONE}},
	[265] = {"linkat", INT, {-OPENAT_DIRFD, -STRING, -OPENAT_DIRFD, -STRING, -INT, NONE}},
	[266] = {"symlinkat", INT, {-STRING, -OPENAT_DIRFD, -STRING, NONE}},
	[267] = {"readlinkat", INT, {-OPENAT_DIRFD, -STRING, MEMSEG, INT, NONE}},
	[268] = {"fchmodat", INT, {-OPENAT_DIRFD, -STRING, -OPEN_MODE, NONE}},
	[269] = {"faccessat", INT, {-OPENAT_DIRFD, -STRING, -ACCESS_MODE, NONE}},
	[270] = {"pselect6",
			 INT,
			 {-INT, -FD_SET_STRUCT, -FD_SET_STRUCT, -FD_SET_STRUCT, -KERNEL_TIMESPEC_STRUCT,
			  -INT_PTR}},
	[271] = {"ppoll",
			 INT,
			 {-FD_SET_STRUCT, -INT, -KERNEL_TIMESPEC_STRUCT, -SIGSET_STRUCT, -INT, NONE}},
	[272] = {"unshare", INT, {-INT, NONE}},
	[273] = {"set_robust_list", INT, {-PTR, -INT, NONE}},
	[274] = {"get_robust_list", INT, {-INT, -PTR, -INT_PTR, NONE}},
	[275] = {"splice", INT, {-INT, -PTR, -INT, -PTR, -INT, -HEX}},
	[276] = {"tee", INT, {-INT, -INT, -INT, -HEX, NONE}},
	[277] = {"sync_file_range", INT, {-INT, -INT, -INT, -HEX, NONE}},
	[278] = {"vmsplice", INT, {-INT, -PTR, -INT, -HEX, NONE}},
	[279] = {"move_pages", INT, {-INT, -INT, -PTR, -PTR, -INT_PTR, -INT}},
	[280] = {"utimensat", INT, {-OPENAT_DIRFD, -STRING, TIMEVAL_STRUCT, -INT, NONE}},
	[281] = {"epoll_pwait",
			 INT,
			 {-INT, EPOLL_EVENT_STRUCT_ARRAY, INT, INT, SIGSET_STRUCT, NONE}},
	[282] = {"signalfd", INT, {-INT, -SIGSET_STRUCT, -INT, NONE}},
	[283] = {"timerfd_create", INT, {-CLOCKID_T, -INT, NONE}},
	[284] = {"eventfd", INT, {-INT, NONE}},
	[285] = {"fallocate", INT, {-INT, -INT, -INT, -INT, NONE}},
	[286] = {"timerfd_settime", INT, {-INT, -TIMER_SETTIME_FLAGS, -KERNEL_ITIMERSPEC_STRUCT, -KERNEL_ITIMERSPEC_STRUCT, NONE}},
	[287] = {"timerfd_gettime", INT, {-INT, -KERNEL_ITIMERSPEC_STRUCT, NONE}},
	[288] = {"accept4", INT, {-INT, SOCKADDR_STRUCT, INT_PTR, -INT, NONE}},
	[289] = {"signalfd4",
			 INT,
			 {-INT, -SIGSET_STRUCT, -INT, -SIGNED_INT, NONE}},
	[290] = {"eventfd2", INT, {-INT, -INT, NONE}},
	[291] = {"epoll_create1", INT, {-INT, NONE}},
	[292] = {"dup3", INT, {-INT, -INT, -OPEN_FLAGS, NONE}},
	[293] = {"pipe2", INT, {PIPEFDS, -OPEN_FLAGS, NONE}},
	[294] = {"inotify_init1", INT, {-INT, NONE}},
	[295] = {"preadv", INT, {-INT, IOVEC_STRUCT, INT, INT, NONE}},
	[296] = {"pwritev", INT, {-INT, -IOVEC_STRUCT, -INT, -INT, NONE}},
	[297] = {"rt_tgsigqueueinfo", INT, {-INT, -INT, -SIGNAL_NAME, -SIGINFO, NONE}},
	[298] = {"perf_event_open", INT, {-PTR, -INT, -INT, -INT, -HEX, NONE}},	
	[299] = {"recvmmsg", INT, {-INT, -PTR, -INT, -HEX, KERNEL_TIMESPEC_STRUCT, NONE}},
	[300] = {"fanotify_init", INT, {-INT, -INT, NONE}},
	[301] = {"fanotify_mark", INT, {-INT, -INT, -HEX, -INT, -STRING, NONE}},
	[302] = {"prlimit64", INT, {-INT, -PRLIMIT_RESOURCE, -RLIMIT64_STRUCT, RLIMIT64_STRUCT, NONE}},
	[303] = {"name_to_handle_at", INT, {-OPENAT_DIRFD, -STRING, -PTR, INT_PTR, INT}},
	[304] = {"open_by_handle_at", INT, {-INT, -PTR, INT, NONE}},
	[305] = {"clock_adjtime", INT, {-CLOCKID_T, -KERNEL_TIMEX_STRUCT, NONE}},
	[306] = {"syncfs", INT, {-INT, NONE}},
	[307] = {"sendmmsg", INT, {-INT, -MSGHDR_STRUCT, -INT, -HEX, SEND_FLAGS}},
	[308] = {"setns", INT, {-INT, -INT}},
	[309] = {"getcpu", INT, {-INT_PTR, -INT_PTR, -PTR, NONE}},
	[310] = {"process_vm_readv", INT, {-INT, -IOVEC_STRUCT, -INT, -IOVEC_STRUCT, -INT, -INT}},
	[311] = {"process_vm_writev", INT, {-INT, -IOVEC_STRUCT, -INT, -IOVEC_STRUCT, -INT, -INT}},
	[312] = {"kcmp", INT, {-INT, -INT, -INT, -INT, -INT, NONE}},
	[313] = {"finit_module", INT, {-INT, -STRING, -INT, NONE}},
	[314] = {"sched_setattr", INT, {-INT, -PTR, -INT, NONE}},
	[315] = {"sched_getattr", INT, {-INT, -PTR, -INT, -INT, NONE}},
	[316] = {"renameat2", INT, {-INT, -STRING, -INT, -STRING, -INT, NONE}},
	[317] = {"seccomp", INT, {-INT, -INT, -PTR, NONE}},
	[318] = {"getrandom", INT, {-PTR, -INT, -INT, NONE}},
	[319] = {"memfd_create", INT, {-STRING, -INT, NONE}},
	[320] = {"kexec_file_load", INT, {-INT, -INT, -INT, -STRING, -INT, NONE}},
	[321] = {"bpf", INT, {-INT, -PTR, -INT, NONE}},
	[322] = {"execveat", INT, {-OPENAT_DIRFD, -STRING, -ARGV, -ENVP, -INT, NONE}},
	[323] = {"userfaultfd", INT, {-INT, NONE}},
	[324] = {"membarrier", INT, {-INT, -INT, NONE}},
	[325] = {"mlock2", INT, {-PTR, -INT, -INT, NONE}},
	[326] = {"copy_file_range", INT, {-INT, -INT_PTR, -INT, -INT_PTR, -INT, NONE}},
	[327] = {"preadv2", INT, {-INT, -IOVEC_STRUCT, -INT, -INT, -INT, NONE}},
	[328] = {"pwritev2", INT, {-INT, -IOVEC_STRUCT, -INT, -INT, -INT, NONE}},
	[329] = {"pkey_mprotect", INT, {-PTR, -INT, -INT, -INT, NONE}},
	[330] = {"pkey_alloc", INT, {-INT, -INT, NONE}},
	[331] = {"pkey_free", INT, {-INT, NONE}},
	[332] = {"statx", INT, {-INT, -STRING, -INT, -HEX, PTR, NONE}},
	[333] = {"io_pgetevents", INT, {-INT, -INT, -INT, -IO_EVENT_STRUCT, -KERNEL_TIMESPEC_STRUCT, NONE}},
	[334] = {"rseq", INT, {-PTR, -HEX, -PTR, -INT, NONE}},
	[424] = {"pidfd_send_signal", INT, {-INT, -SIGNAL_NAME, -SIGINFO, -INT, NONE}},
	[425] = {"io_uring_setup", INT, {-INT, -PTR, NONE}},
	[426] = {"io_uring_enter", INT, {-INT, -INT, -INT, -INT, -PTR, -INT}},
	[427] = {"io_uring_register", INT, {-INT, -INT, -INT, NONE}},
	[428] = {"open_tree", INT, {-INT, -STRING, -INT, NONE}},
	[429] = {"move_mount", INT, {-INT, -STRING, -INT, -STRING, -MOUNT_FLAGS, NONE}},
	[430] = {"fsopen", INT, {-STRING, -INT, NONE}},
	[431] = {"fsconfig", INT, {-INT, -INT, -INT, NONE}},
	[432] = {"fsmount", INT, {-INT, -INT, -INT, -INT, NONE}},
	[433] = {"fspick", INT, {-INT, -INT, -INT, NONE}},
	[434] = {"pidfd_open", INT, {-INT, -INT, NONE}},
	[435] = {"clone3", INT, {-INT, -INT, -INT, -INT, -INT, NONE}},
	[436] = {"close_range", INT, {-INT, -INT, NONE}},
};