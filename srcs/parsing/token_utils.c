/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:38:53 by tchalaou          #+#    #+#             */
/*   Updated: 2024/08/12 13:12:43 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env, char *key)
{
	t_env	*current;
	int		len;

	current = env;
	len = ft_strlen(key);
	while (current)
	{
		if (current->key && current->value)
		{
			if (!ft_strncmp(key, current->key, len) && !current->key[len])
				return (current->value);
		}
		current = current->next;
	}
	return ("");
}

void	join_replace(char **word, char **value)
{
	char	*tmp;

	tmp = ft_strjoin(*word, *value);
	free(*value);
	free(*word);
	*word = tmp;
}

t_token	*create_token(t_env *env)
{
	t_token	*token;

	token = ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (NULL);
	token->id = 0;
	token->env = env;
	return (token);
}

void	token_add_back(t_token **token, t_token *add)
{
	if (!add)
		return ;
	if (!*token)
		*token = add;
	else
	{
		while (*token)
			token = &(*token)->next;
		*token = add;
	}
}

void	free_token(t_token **token)
{
	t_token	*current;

	while (*token)
	{
		current = *token;
		*token = current->next;
		if (current->word)
			free(current->word);
		free(current);
	}
}
