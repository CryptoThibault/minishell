/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:38:53 by tchalaou          #+#    #+#             */
/*   Updated: 2024/07/24 18:08:45 by tchalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env, char *key)
{
	t_env	*current;
	int		key_len;

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

t_token	*create_token(t_env *env)
{
	t_token	*token;

	token = ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (NULL);
	token->id = -1;
	token->word = NULL;
	token->env = env;
	token->next = NULL;
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
