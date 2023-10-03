NAME := ft_strace
CC := cc
CFLAGS := -Wall -Wextra -Werror
LIBFTDIR := libft
LIBFT := $(LIBFTDIR)/libft.a
LIBFT_DEBUG := $(LIBFTDIR)/debug_libft.a
LIBFTINC := $(LIBFTDIR)/includes
LIBS :=

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

SRCS += utils/log_error.c

# execution srcs

SRCS += execution/search_in_path.c \
		execution/exec_program.c

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

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(LIBFT_DEBUG):
	$(MAKE) -C $(LIBFTDIR) debug

$(NAME): $(LIBFT) $(OBJS_RELEASE) $(OBJS_MAIN_RELEASE)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS_RELEASE) $(OBJS_MAIN_RELEASE) $(LIBS) -L $(LIBFTDIR) -lft

$(NAME_DEBUG): $(LIBFT_DEBUG) $(OBJS_DEBUG) $(OBJS_MAIN_DEBUG)
	$(CC) $(CFLAGS) -o $(NAME_DEBUG) $(OBJS_DEBUG) $(OBJS_MAIN_DEBUG) $(LIBS) -L $(LIBFTDIR) -lftdebug

debug: $(NAME_DEBUG)

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

.PHONY: all clean fclean re debug redebug