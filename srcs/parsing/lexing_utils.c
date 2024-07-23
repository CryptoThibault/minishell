/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:15:51 by tchalaou          #+#    #+#             */
/*   Updated: 2024/07/23 16:19:40 by tchalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(t_env *env)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->id = -1;
	token->word = NULL;
	token->env = env;
	token->next = NULL;
	return (token);
}

int	is_whitespace(char c)
{
	return (c != ' ' && c != '\t' && c != '\v' && c != '\n');
}

int	word_len(char *line, int start)
{
	int	len;

	len = 0;
	while (line[start] && !ft_strchr(" \t\n;<>|'\"$", line[start]))
	{
		len++;
		start++;
	}
	return (len);
}

char	*get_value(t_env *env, char *key)
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

void	token_add_back(t_token **token, t_token *new)
{
	if (!new)
		return ;
	if (!*token)
		*token = new;
	else
	{
		while (*token)
			token = &(*token)->next;
		*token = new;
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
