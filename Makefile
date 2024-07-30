NAME = minishell
CC = cc

LIBFT = libft
CFLAGS = -Wall -Wextra -Werror -Iincludes

SRCS =	srcs/main.c \
	srcs/exec/child.c srcs/exec/heredoc.c \
	srcs/parsing/get_msh.c srcs/parsing/parsing_utils.c \
	srcs/parsing/fill_token.c srcs/parsing/token_utils.c \
	srcs/parsing/fill_msh.c srcs/parsing/msh_utils.c \
	srcs/builtins/echo.c srcs/builtins/cd.c srcs/builtins/pwd.c \
	srcs/builtins/exit.c srcs/builtins/export.c \
	srcs/builtins/env.c srcs/builtins/unset.c

OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)/$(LIBFT).a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT) -lft -lreadline

-include $(DEPS)

$(LIBFT)/$(LIBFT).a:
	make -C $(LIBFT)

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C $(LIBFT) clean
	rm -f $(OBJS) $(DEPS)

fclean: clean
	make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
