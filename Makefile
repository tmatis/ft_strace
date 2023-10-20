NAME := ft_strace
CC := cc
CFLAGS := -Wall -Wextra -Werror
LIBFTDIR := libft
LIBFT := $(LIBFTDIR)/libft.a
LIBFT_DEBUG := $(LIBFTDIR)/libftdebug.a
LIBFTINC := $(LIBFTDIR)/includes
LIBS :=
FORMAT_COMMAND := clang-format -i -style=file

ifneq ($(filter debug redebug,$(MAKECMDGOALS)),)
	CFLAGS += -g
endif

SRCSDIR := srcs
OBJSDIR_RELEASE := .build/release
OBJSDIR_DEBUG := .build/debug
INCDIR := includes

SRCS_MAIN := main.c

# config srcs

SRCS += config.c

# utils srcs

SRCS += utils/log_error.c \
		utils/initial_wait.c

# execution srcs

SRCS += execution/search_in_path.c \
		execution/exec_program.c \
		execution/setup_tracing.c

# analysis srcs

SRCS += analysis/analysis_routine.c

# syscall srcs

SRCS += syscall/syscall_get_description.c \
		syscall/syscall_log.c \
		syscall/syscall_log_param.c  \
		syscall/syscall_is_execve.c \
		syscall/param_log/utils/flags_log.c \
		syscall/param_log/utils/option_log.c \
		syscall/param_log/utils/remote_memcpy.c \
		syscall/param_log/utils/handle_ptr.c \
		syscall/param_log/log_int.c \
		syscall/param_log/log_signed_int.c \
		syscall/param_log/log_none.c \
		syscall/param_log/log_ptr.c \
		syscall/param_log/log_hex.c \
		syscall/param_log/log_memseg.c \
		syscall/param_log/log_string.c \
		syscall/param_log/log_open_flags.c \
		syscall/param_log/log_open_mode.c \
		syscall/param_log/log_stat_struct.c \
		syscall/param_log/log_poll_fds.c \
		syscall/param_log/log_poll_fds_after.c \
		syscall/param_log/log_seek_whence.c \
		syscall/param_log/log_mmap_prot.c \
		syscall/param_log/log_mmap_flags.c \
		syscall/param_log/log_signal_name.c \
		syscall/param_log/log_sigaction_struct.c \
		syscall/param_log/log_sigset_struct.c \
		syscall/param_log/log_sigprocmask_how.c \
		syscall/param_log/log_iovec_struct.c \
		syscall/param_log/log_access_mode.c \
		syscall/param_log/log_pipefds.c \
		syscall/param_log/log_fd_set_struct.c \
		syscall/param_log/log_timeval_struct.c \
		syscall/param_log/log_select_return.c \
		syscall/param_log/log_mremap_flags.c \
		syscall/param_log/log_msync_flags.c \
		syscall/param_log/log_madvise_advise.c \
		syscall/param_log/log_shmat_flags.c \
		syscall/param_log/log_shmid_ds_struct.c \
		syscall/param_log/log_shmctl_cmd.c \
		syscall/param_log/log_kernel_timespec_struct.c \
		syscall/param_log/log_itimerval_struct.c \
		syscall/param_log/log_itimer_which.c \
		syscall/param_log/log_address_family.c \
		syscall/param_log/log_socket_type.c \
		syscall/param_log/log_ipproto.c \
		syscall/param_log/log_sockaddr_struct.c \
		syscall/param_log/log_send_flags.c \
		syscall/param_log/log_msghdr_struct.c \
		syscall/param_log/log_int_ptr.c \
		syscall/param_log/log_shutdown_how.c \
		syscall/param_log/log_argv.c \
		syscall/param_log/log_envp.c \
		syscall/param_log/log_wait_options.c \
		syscall/param_log/log_wait_status.c \
		syscall/param_log/log_rusage_struct.c \
		syscall/param_log/log_utsname_struct.c \
		syscall/param_log/log_sembuf_struct.c \
		syscall/param_log/log_ipcs_flags.c \
		syscall/param_log/log_semctl_cmd.c \
		syscall/param_log/log_msgbuf_struct.c \
		syscall/param_log/log_msgflg.c \
		syscall/param_log/log_msgctl_cmd.c \
		syscall/param_log/log_msqid_ds_struct.c \
		syscall/param_log/log_fcntl_cmd.c \
		syscall/param_log/log_flock_cmd.c \
		syscall/param_log/log_timezone_struct.c \
		syscall/param_log/log_rlimit_resource.c \
		syscall/param_log/log_rlimit_struct.c \
		syscall/param_log/log_rusage_who.c \
		syscall/param_log/log_sysinfo_struct.c \
		syscall/param_log/log_tms_struct.c \
		syscall/param_log/log_ptrace_request.c \
		syscall/param_log/log_syslog_type.c \
		syscall/syscall_handle.c \

# registers srcs

SRCS += registers/registers_get_param.c \
		registers/registers_get_return.c \
		registers/registers_get_syscall.c \
		registers/registers_get_type.c

# signals srcs

SRCS += signals/signals_block.c \
		signals/signals_handle.c

OBJS_MAIN_RELEASE := $(addprefix $(OBJSDIR_RELEASE)/,$(SRCS_MAIN:.c=.o))
OBJS_MAIN_DEBUG := $(addprefix $(OBJSDIR_DEBUG)/,$(SRCS_MAIN:.c=.o))
OBJS_RELEASE := $(addprefix $(OBJSDIR_RELEASE)/,$(SRCS:.c=.o))
OBJS_DEBUG := $(addprefix $(OBJSDIR_DEBUG)/,$(SRCS:.c=.o))

ALL_SRCS := $(SRCS) $(SRCS_MAIN)

DEPS_RELEASE := $(addprefix $(OBJSDIR_RELEASE)/,$(ALL_SRCS:.c=.d))
DEPS_DEBUG := $(addprefix $(OBJSDIR_DEBUG)/,$(ALL_SRCS:.c=.d))

DFLAGS	= -MMD -MF $(@:.o=.d)

NAME_DEBUG := $(NAME)_debug

all: $(NAME)

debug: $(NAME_DEBUG)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(LIBFT_DEBUG):
	$(MAKE) -C $(LIBFTDIR) debug

$(NAME): $(LIBFT) $(OBJS_RELEASE) $(OBJS_MAIN_RELEASE)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS_RELEASE) $(OBJS_MAIN_RELEASE) $(LIBS) -L $(LIBFTDIR) -lft

$(NAME_DEBUG): $(LIBFT_DEBUG) $(OBJS_DEBUG) $(OBJS_MAIN_DEBUG)
	$(CC) $(CFLAGS) -o $(NAME_DEBUG) $(OBJS_DEBUG) $(OBJS_MAIN_DEBUG) $(LIBS) -L $(LIBFTDIR) -lftdebug


unit: $(LIBFT) $(OBJS_DEBUG)
	libft/scripts/car.sh $(OBJS_DEBUG)

-include $(DEPS_RELEASE)
$(OBJSDIR_RELEASE)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INCDIR) -I $(LIBFTINC) $(DFLAGS) -c $< -o $@

-include $(DEPS_DEBUG)
$(OBJSDIR_DEBUG)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INCDIR) -I $(LIBFTINC) $(DFLAGS) -c $< -o $@

clean:
	make -C $(LIBFTDIR) clean
	rm -rf .build

fclean: clean
	make -C $(LIBFTDIR) fclean
	rm -f $(NAME) $(NAME_DEBUG)

re: fclean all

redebug: fclean debug

format:
	find . -regex '.*\.\(c\|h\)' -exec $(FORMAT_COMMAND) {} \;

.PHONY: all clean fclean re debug redebug