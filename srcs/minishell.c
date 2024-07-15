/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:14:30 by tchalaou          #+#    #+#             */
/*   Updated: 2024/07/15 17:48:58 by tchalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_equal(char *var)
{
	int		i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '+' || var[i] == '=')
		{
			if(var[i] == '+' && var[i+1] == '=')
				return(2);
			return (1);	
		}
		i++;
	}
	return (0);
}

char *get_var_name(char *var)
{
	int	i;
	
	i = 0;
	if (!is_equal(var))
		return (ft_strdup(var));
	while (var[i] != '=')
		i++;
	if(var[i - 1] == '+')
		i--;
	return (ft_substr(var, 0, i));
}

char *get_var(char *var)
{
	int		i;

	i = 0;
	if (!is_equal(var))
		return (ft_strdup(""));
	while (var[i] != '=')
		i++;
	return (ft_substr(var, i + 1, (ft_strlen(var) - i)));
}

int	split_env(t_env *env)
{
	t_env *current;

	current = env;
	while (current)
	{
		current->var = get_var(current->full_var);
		if (!current->var)
			return (1);
		current->var_name = get_var_name(current->full_var);
		if (!current->var)
			return (1);
		current->set = true;
		current = current->next;
	}
	return (0);
}

t_env	*ft_envlastnode(t_env *lst)
{
	t_env	*current;

	if (!lst)
		return (0);
	current = lst;
	while (current->next)
		current = current->next;
	return (current);
}

void	add_env_node(t_env **lst, t_env *add)
{
	if (!lst || !add)
		return ;
	if (!*lst)
		*lst = add;
	else
		ft_envlastnode(*lst)->next = add;
}

t_env *create_env_node(char **envp, int i)
{
	t_env *env;
	
	env = ft_calloc(sizeof(t_env), 1);
	if (!env)
		return (NULL);
	env->set = 1;
	// printf("%d\n", env->set);
	env->full_var = ft_strdup(envp[i]);
	if (!env->full_var)
		return (NULL);
	return (env);
}

t_env *env_into_list(char **envp)
{
	t_env *env;
	t_env *tmp;
	int	i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		tmp = create_env_node(envp, i);
		add_env_node(&env, tmp);
		i++;
	}
	split_env(env);
	return (env);
}

int	free_env(t_env *env)
{
	t_env *current;
	t_env *prev;

	current = env;
	while (current)
	{
		prev = current;
		free(current->full_var);
		free(current->var);
		free(current->var_name);
		current = current->next;
		free(prev);
	}
	return (0);
}

int	main(void)
{
	char	*line;
	extern char	**environ;
	t_env	*env;
	t_token *token;
	t_msh	*msh;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	env = env_into_list(environ);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (!ft_strlen(line))
			continue ;
		add_history(line);
		token = lexing(line, env);
		free(line);
		msh = parsing(token);
		free_token(&token);
		execute(msh);
		free_msh(&msh);
	}
	free_env(env);
	return (0);
}
