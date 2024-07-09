/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:15:54 by tchalaou          #+#    #+#             */
/*   Updated: 2024/07/09 16:03:06 by tchalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <curses.h>
# include <limits.h>

# define WORD 1
# define SMALLER 2
# define BIGGER 3
# define PIPE 4
# define DOLLAR 5

typedef struct	s_var
{
	char		*key;
	char		*value;
	struct s_var	*next;
}		t_var;

typedef struct s_token
{
	int		id;
	char		*word;
	struct s_token	*next;
}		t_token;

typedef struct s_msh
{
	int		index;
	char	**cmd;
	char	*infile;
	char	*outfile;
	int		here_doc;
	int		append;
	int		in_fd;
	int		out_fd;
	int		pipefd[2];
	struct s_msh	*next;
	struct s_msh	*prev;
}		t_msh;

t_var	*create_var(char *key, char *value);
void	update_var(t_var *var, char *key, char *value);
int	check_var(t_var *var, char *key);
void	varadd_back(t_var **var, t_var *new);
void	set_var(t_var **var, char *key, char *value);
void	free_var(t_var **var);

t_token	*create_token(int id, char *word);
int	is_whitespace(char c);
int	word_len(char *line, int start);
void	fill_word(char **word, char *line, int *i);
int	fill_token(char **word, char *line, int *i);
void	tokenadd_back(t_token **token, t_token *new);
t_token	*lexing(char *line);
void	free_token(t_token **token);

t_msh	*create_msh(int index);
int	count_words(t_token *token);
void	fill_command(t_msh *msh, t_token **token);
void	fill_smaller(t_msh *msh, t_token **token);
void	fill_bigger(t_msh *msh, t_token **token);
void	fill_msh(t_msh *msh, t_token **token);
t_msh	*mshget_last(t_msh *msh);
void	mshadd_back(t_msh **msh, t_msh *new);
t_msh	*parsing(t_token *token);
void	free_msh(t_msh **msh);

int		array_size(char **array);
void	free_array(char **array);
void	sigint_handler(int sig);
void	sigquit_handler(int sig);

void	execute(t_msh *msh);

void	builtins(int ac, char **av);
void	cmd_echo(int ac, char **av);
void	cmd_cd(int ac, char **av);
void	cmd_pwd(int ac, char **av);
void	cmd_export(int ac, char **av);
void	cmd_unset(int ac, char **av);
void	cmd_env(int ac, char **av);
void	cmd_exit(int ac, char **av);

#endif
