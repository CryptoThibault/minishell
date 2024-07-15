/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:51:23 by tchalaou          #+#    #+#             */
/*   Updated: 2024/07/15 13:20:41 by tchalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_word(char **word, char *line, int *i)
{
	int	j;

	*word = malloc(word_len(line, *i) + 1);
	if (!*word)
		return ;
	j = 0;
	while (line[*i] && !ft_strchr(" \t\n;<>|$", line[*i]))
	{
		(*word)[j++] = line[*i];
		(*i)++;
	}
	(*word)[j] = 0;
	(*i)--;
}

void	fill_quote(char **word, char *line, int *i)
{
	int	j;
	int	len;

	(*i)++;
	j = *i;
	len = 0;
	while (line[j] && line[j++] != '\'')
		len++;
	*word = malloc(len + 1);
	if (!*word)
		return ;
	j = 0;
	while (line[*i] && line[*i] != '\'')
	{
		(*word)[j++] = line[*i];
		(*i)++;
	}
	(*word)[j] = 0;
	if (line[*i] == '\'')
		(*i)++;
}

void	fill_doublequote(char **word, char *line, int *i)
{
	int	j;
	int	len;

	(*i)++;
	j = *i;
	len = 0;
	while (line[j] && line[j++] != '"')
		len++;
	*word = malloc(len + 1);
	if (!*word)
		return ;
	j = 0;
	while (line[*i] && line[*i] != '"')
	{
		(*word)[j++] = line[*i];
		(*i)++;
	}
	(*word)[j] = 0;
	if (line[*i] == '"')
		(*i)++;
}

int	fill_token(char **word, char *line, int *i)
{
	while (!is_whitespace(line[*i]))
		(*i)++;
	if (!line[*i])
		return (0);
	if (line[*i] == '\'')
	{
		fill_quote(word, line, i);
		return (WORD);
	}
	else if (line[*i] == '"')
	{
		fill_doublequote(word, line, i);
		return (WORD);
	}
	else if (line[*i] == '<')
		return (SMALLER);
	else if (line[*i] == '>')
		return (BIGGER);
	else if (line[*i] == '|')
		return (PIPE);
	else if (line[*i] == '$')
		return (DOLLAR);
	else
	{
		fill_word(word, line, i);
		return (WORD);
	}
}

t_token	*lexing(char *line)
{
	t_token	*token;
	int		i;
	int		id;
	char	*word;

	token = NULL;
	i = -1;
	while (line[++i])
	{
		word = NULL;
		id = fill_token(&word, line, &i);
		if (!id)
			break ;
		tokenadd_back(&token, create_token(id, word));
	}
	return (token);
}

/*
int	main()
{
	t_token	*token;
	t_token *start;

	token = lexing(" aa; <bb> | $cc ");
	start = token;
	while (token)
	{
		printf("id: %d\n", token->id);
		if (token->word)
			printf("word: %s\n", token->word);
		token = token->next;
	}
	free_token(&start);
	return (0);
}*/
