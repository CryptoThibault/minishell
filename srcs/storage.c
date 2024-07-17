/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:06:46 by tchalaou          #+#    #+#             */
/*   Updated: 2024/07/15 17:50:25 by tchalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	env->next = NULL;
	return (env);
}

void	split_key_value(char *str, char **key, char **value)
{
	char	*equal;

	equal = ft_strchr(str, '=');
	if (equal)
	{
		*equal = '\0';
		*key = str;
		*value = equal + 1;
	}
	else
	{
		*key = str;
		*value = NULL;
	}
}

void	env_add_back(t_env **env, t_env *new)
{
	if (!new)
		return ;
	if (!*env)
		*env = new;
	else
	{
		while (*env)
			env = &(*env)->next;
		*env = new;
	}
}

t_env	*get_env(void)
{
	extern char	**environ;
	t_env	*env;
	t_env	*new;
	int		i;
	char	*key;
	char	*value;

	env = NULL;
	i = -1;
	while (environ[++i])
	{
		split_key_value(environ[i], &key, &value);
		new = create_env(key, value);
		if (!new)
		{
			free_env(&env);
			return (NULL);
		}
		env_add_back(&env, new);
	}
	return (env);
}

void	free_env(t_env **env)
{
	t_env	*current;

	while (*env)
	{
		current = *env;
		*env = current->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		free(current);
	}
}

char	*get_value(t_env *env, char *key)
{
	t_env	*current;
	int	key_len;

	current = env;
	key_len = ft_strlen(key);
	while (current)
	{
		if (!ft_strncmp(key, current->key, key_len) && !current->key[key_len])
			return (current->value);
		current = current->next;
	}
	return ("");
}

void	print_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}
/*
int	main(void)
{
	t_env	*env;

	env = get_env();
	print_env(env);
	free_env(&env);
	return(0);
}*/
