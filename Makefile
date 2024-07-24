NAME = minishell
CC = cc
LIB = libft
CFLAGS = -Wall -Wextra -Werror -Iincludes -g3

SRCS =	src/main.c \
	src/exec/child.c \
	src/exec/heredoc.c \
	src/parsing/get_msh.c \
	src/parsing/parsing_utils.c \
	src/parsing/fill_token.c \
	src/parsing/token_utils.c \
	src/parsing/fill_msh.c \
	src/parsing/msh_utils.c \
	src/builtins/echo.c \
	src/builtins/cd.c \
	src/builtins/pwd.c \
	src/builtins/exit.c \
	src/builtins/export.c \
	src/builtins/env.c \
	src/builtins/unset.c

OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS) $(LIB)/$(LIB).a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIB) -lft -lreadline

-include $(DEPS)

$(LIB)/$(LIB).a:
	make -C $(LIB)

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C $(LIB) clean
	rm -f $(OBJS) $(DEPS)

fclean: clean
	make -C $(LIB) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft
