#include "../param_log/param_log.h"
#include <ft_printf.h>
#include <registers.h>
#include <sys/types.h>
#include <macros.h>
/*
 * cloning flags:
 */
#define CSIGNAL 0x000000ff		 /* signal mask to be sent at exit */
#define CLONE_VM 0x00000100		 /* set if VM shared between processes */
#define CLONE_FS 0x00000200		 /* set if fs info shared between processes */
#define CLONE_FILES 0x00000400	 /* set if open files shared between processes */
#define CLONE_SIGHAND 0x00000800 /* set if signal handlers and blocked signals shared */
#define CLONE_PIDFD 0x00001000	 /* set if a pidfd should be placed in parent */
#define CLONE_PTRACE 0x00002000	 /* set if we want to let tracing continue on the child too */
#define CLONE_VFORK 0x00004000	 /* set if the parent wants the child to wake it up on mm_release */
#define CLONE_PARENT 0x00008000	 /* set if we want to have the same parent as the cloner */
#define CLONE_THREAD 0x00010000	 /* Same thread group? */
#define CLONE_NEWNS 0x00020000	 /* New mount namespace group */
#define CLONE_SYSVSEM 0x00040000 /* share system V SEM_UNDO semantics */
#define CLONE_SETTLS 0x00080000	 /* create a new TLS for the child */
#define CLONE_PARENT_SETTID 0x00100000	/* set the TID in the parent */
#define CLONE_CHILD_CLEARTID 0x00200000 /* clear the TID in the child */
#define CLONE_DETACHED 0x00400000		/* Unused, ignored */
#define CLONE_UNTRACED                                                                             \
	0x00800000 /* set if the tracing process can't force CLONE_PTRACE on this clone */
#define CLONE_CHILD_SETTID 0x01000000 /* set the TID in the child */
#define CLONE_NEWCGROUP 0x02000000	  /* New cgroup namespace */
#define CLONE_NEWUTS 0x04000000		  /* New utsname namespace */
#define CLONE_NEWIPC 0x08000000		  /* New ipc namespace */
#define CLONE_NEWUSER 0x10000000	  /* New user namespace */
#define CLONE_NEWPID 0x20000000		  /* New pid namespace */
#define CLONE_NEWNET 0x40000000		  /* New network namespace */
#define CLONE_IO 0x80000000			  /* Clone io context */

flag_str_t clone_flags[] = {
    FLAG_STR(CLONE_VM),
    FLAG_STR(CLONE_FS),
    FLAG_STR(CLONE_FILES),
    FLAG_STR(CLONE_SIGHAND),
    FLAG_STR(CLONE_PIDFD),
    FLAG_STR(CLONE_PTRACE),
    FLAG_STR(CLONE_VFORK),
    FLAG_STR(CLONE_PARENT),
    FLAG_STR(CLONE_THREAD),
    FLAG_STR(CLONE_NEWNS),
    FLAG_STR(CLONE_SYSVSEM),
    FLAG_STR(CLONE_SETTLS),
    FLAG_STR(CLONE_PARENT_SETTID),
    FLAG_STR(CLONE_CHILD_CLEARTID),
    FLAG_STR(CLONE_DETACHED),
    FLAG_STR(CLONE_UNTRACED),
    FLAG_STR(CLONE_CHILD_SETTID),
    FLAG_STR(CLONE_NEWCGROUP),
    FLAG_STR(CLONE_NEWUTS),
    FLAG_STR(CLONE_NEWIPC),
    FLAG_STR(CLONE_NEWUSER),
    FLAG_STR(CLONE_NEWPID),
    FLAG_STR(CLONE_NEWNET),
    FLAG_STR(CLONE_IO),
};

/**
 * @brief A custom handle for 'clone' syscall since it act weird
 *
 * @param pid the pid of the tracee
 * @param regs the registers
 * @param regs_type the registers types
 * @return int the size written
 */
int custom_handler_clone(pid_t pid, user_regs_t *regs, register_type_t regs_type)
{
    (void)pid;
	uint64_t child_stack = registers_get_param(regs, regs_type, 2);
	uint64_t flags = registers_get_param(regs, regs_type, 0);
	uint64_t child_tidptr = registers_get_param(regs, regs_type, 3);

	int size_written = 0;
	size_written += ft_dprintf(STDERR_FILENO, "child_stack=");
    size_written += log_PTR(child_stack);
    size_written += ft_dprintf(STDERR_FILENO, ", flags=");
    size_written += flags_log(flags, clone_flags, ELEM_COUNT(clone_flags));
    size_written += ft_dprintf(STDERR_FILENO, ", child_tidptr=");
    size_written += log_PTR(child_tidptr);
    return size_written;
}