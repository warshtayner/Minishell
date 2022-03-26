NAME	=	minishell
SRCS	=	src/main.c src/ft_list.c src/cmd_split.c \
			from_libft/ft_split.c from_libft/ft_strlen.c from_libft/ft_substr.c \
			src/ft_count_arg.c src/free_list.c src/env.c src/ft_list_list.c \
			src/check_flag.c src/add_ft_split.c src/dollar.c src/parsing.c\
			src/redirect.c \
			execute/execute.c	execute/find_value_env.c	execute/work_with_char_env.c\
			execute/shell_commands.c	execute/check_signal.c	execute/find_built.c\
			execute/redirects.c	\
			libft/ft_strnstr.c	libft/ft_strjoin.c	libft/ft_putstr_fd.c \
			libft/ft_strdup.c	libft/ft_strncmp.c\
			libft/ft_atoi.c	libft/ft_itoa.c	libft/ft_lstadd_back.c	\
			libft/ft_lstnew.c	libft/ft_lstlast.c	libft/ft_lstsize.c	\
			builts/pwd_built.c	builts/exit_built.c	builts/cd_built.c \
			builts/env_built.c	builts/cd_built_utils.c	builts/export_built.c\
			builts/print_sort_env_utils.c	builts/unset_built.c	builts/echo_built.c\
			pipe/pipe.c \

HEADER	=	include/minishell.h
OBJ		=	$(SRCS:%.c=%.o)
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -I$(HEADER)

.PHONY	:	all clean fclean re

all		:	$(NAME)

$(NAME)	:	$(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) -lreadline -ltermcap -g -L/Users/$(USER)/.brew/opt/readline/lib/ -I/Users/$(USER)/.brew/opt/readline/include -o $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean	:
	@rm -f $(OBJ)

fclean	:	clean
	@$(RM) $(NAME)

re		:	fclean all