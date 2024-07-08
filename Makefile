NAME = minishell
LIB = libft
FILES = srcs/minishell.c \
	srcs/array.c \
	srcs/handler.c \
	srcs/storage.c \
	srcs/execute.c \
	srcs/parsing/lexing.c \
	srcs/parsing/parsing.c
FLAGS = -Wall -Wextra -Werror

$(NAME): libft
	cc $(FLAGS) -o $@ $(FILES) -I includes -lreadline
all: $(NAME)

clean:
	rm -f *.out
fclean: clean
	rm  -f $(NAME)
re: fclean  all

libft:
	make -C $(LIB)
