/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:36:44 by tchalaou          #+#    #+#             */
/*   Updated: 2024/08/13 13:01:54 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_value(t_token *token, char *line, int *i)
{
	char	*key;
	char	*value;
	int		k;

	(*i)++;
	key = ft_calloc(sizeof(char), word_len(line, *i) + 1);
	if (!key)
		return ;
	k = 0;
	while (line[*i] && !ft_strchr(" \t\n<>|'\"$", line[*i]))
	{
		key[k++] = line[*i];
		(*i)++;
	}
	if (key && !ft_strcmp(key, "?"))
		value = ft_itoa(token->env->ex_code);
	else if (!ft_strlen(key))
		value = ft_strdup("$");
	else
		value = ft_strdup(get_env_value(token->env, key));
	free(key);
	if (value || *value)
		join_replace(&token->word, &value);
}

void	fill_word(t_token *token, char *line, int *i)
{
	int	j;

	token->id = WORD;
	token->word = ft_calloc(sizeof(char), word_len(line, *i) + 1);
	if (!token->word)
		return ;
	j = 0;
	while (line[*i] && !ft_strchr(" \t\n<>|'\"", line[*i]))
	{
		if (line[*i] == '$')
		{
			fill_value(token, line, i);
			(*i)--;
			return ;
		}
		token->word[j] = line[*i];
		j++;
		(*i)++;
	}
	(*i)--;
}

void	fill_quote(t_token *token, char *line, int *i)
{
	int	j;
	int	len;

	token->id = WORD;
	j = ++(*i);
	len = 0;
	while (line[j] && line[j++] != '\'')
		len++;
	token->word = ft_calloc(sizeof(char), len + 1);
	if (!token->word)
		return ;
	j = 0;
	while (line[*i] && line[*i] != '\'')
		token->word[j++] = line[(*i)++];
	if (line[*i] != '\'')
		(*i)--;
}

void	fill_doublequote(t_token *token, char *line, int *i)
{
	int	j;
	int	len;

	token->id = WORD;
	j = ++(*i);
	len = 0;
	while (line[j] && line[j++] != '"')
		len++;
	token->word = ft_calloc(sizeof(char), len + 1);
	if (!token->word)
		return ;
	j = 0;
	while (line[*i] && line[*i] != '"')
	{
		if (line[*i] == '$')
		{
			fill_value(token, line, i);
			break ;
		}
		token->word[j++] = line[(*i)++];
	}
	if (line[*i] != '"')
		(*i)--;
}

void	fill_token(t_token *token, char *line, int *i)
{
	while (!is_whitespace(line[*i]))
		(*i)++;
	if (!line[*i])
		return ;
	if (line[*i] == '\'')
		fill_quote(token, line, i);
	else if (line[*i] == '"')
		fill_doublequote(token, line, i);
	else if (line[*i] == '<')
		token->id = SMALLER;
	else if (line[*i] == '>')
		token->id = BIGGER;
	else if (line[*i] == '|')
		token->id = PIPE;
	else
		fill_word(token, line, i);
}
