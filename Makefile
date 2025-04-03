NAME = minishell

LIBRARY_DIR = ./libft
LIBFT = $(LIBRARY_DIR)/libft.a

CC = cc

#CFLAGS = -Wall -Wextra -I includes/ -I libft/ 
CFLAGS = -Wall -Wextra -I includes/ -I libft/ -I/opt/homebrew/opt/readline/include -fsanitize=address

LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline

RM = rm -f

SRCS = 	main.c
SRCS +=	src/parsing/init.c
SRCS +=	src/parsing/token_parser.c
SRCS +=	src/parsing/token_types.c
SRCS +=	src/parsing/redir.c
SRCS +=	src/parsing/redir_heredoc.c
SRCS +=	src/parsing/redir_utils.c
SRCS +=	src/expand/expand.c
SRCS +=	src/expand/expand_utils.c
SRCS +=	src/execution/execute_cmd.c
SRCS +=	src/execution/try_to_exec_cmd.c
SRCS +=	src/execution/pipe.c
SRCS +=	src/execution/builtin_executor.c
SRCS +=	src/environment/environment.c
SRCS +=	src/environment/environment_mshell.c
SRCS +=	src/environment/path.c
SRCS +=	src/builtins/pwd.c
SRCS +=	src/builtins/echo.c
SRCS +=	src/builtins/env.c
SRCS +=	src/builtins/export.c
SRCS +=	src/builtins/export_utils.c
SRCS +=	src/builtins/unset.c
SRCS +=	src/builtins/cd.c
SRCS +=	src/builtins/cd_utils.c
SRCS +=	src/builtins/exit.c
SRCS +=	src/signals/signals.c
SRCS +=	src/utils/utils.c
SRCS +=	src/utils/utils_2.c
SRCS +=	src/utils/utils_3.c
SRCS +=	src/utils/utils_4.c
SRCS +=	src/utils/ft_realloc.c
SRCS +=	src/utils/ft_free_two_dim_array.c
SRCS +=	src/utils/ft_print_and_set_error.c
SRCS +=	src/utils/free_paths_and_return.c

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBRARY_DIR) all

clean:
	@$(MAKE) -C $(LIBRARY_DIR) clean
	@$(RM) $(OBJS)

fclean: clean
	@$(MAKE) -C $(LIBRARY_DIR) fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
