/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:15:51 by tchalaou          #+#    #+#             */
/*   Updated: 2024/07/15 13:17:51 by tchalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(int id, char *word)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->id = id;
	token->word = word;
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
	while (line[start] && !ft_strchr(" \t\n;<>|$", line[start]))
	{
		len++;
		start++;
	}
	return (len);
}

void	tokenadd_back(t_token **token, t_token *new)
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
