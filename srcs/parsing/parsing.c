/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:02:41 by tchalaou          #+#    #+#             */
/*   Updated: 2024/07/15 13:28:32 by tchalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_command(t_msh *msh, t_token **token)
{
	int	i;

	msh->cmd = malloc(sizeof(char *) * (count_words(*token) + 1));
	if (!msh->cmd)
		return ;
	i = -1;
	while (*token && (*token)->id == WORD)
	{
		msh->cmd[++i] = ft_strdup((*token)->word);
		*token = (*token)->next;
	}
	msh->cmd[++i] = NULL;
}

void	fill_smaller(t_msh *msh, t_token **token)
{
	*token = (*token)->next;
	if ((*token)->id == SMALLER)
	{
		*token = (*token)->next;
		msh->here_doc = 1;
	}
	if ((*token)->id == WORD)
	{
		msh->infile = ft_strdup((*token)->word);
		*token = (*token)->next;
	}
	else
		printf("msh: parse error");
}

void	fill_bigger(t_msh *msh, t_token **token)
{
	*token = (*token)->next;
	if ((*token)->id == BIGGER)
	{
		*token = (*token)->next;
		msh->append = 1;
	}
	if ((*token)->id == WORD)
	{
		msh->outfile = ft_strdup((*token)->word);
		*token = (*token)->next;
	}
	else
		printf("msh: parse error");
}

void	fill_msh(t_msh *msh, t_token **token)
{
	while (*token)
	{
		if ((*token)->id == WORD)
			fill_command(msh, token);
		else if ((*token)->id == SMALLER)
			fill_smaller(msh, token);
		else if ((*token)->id == BIGGER)
			fill_bigger(msh, token);
		else if ((*token)->id == PIPE)
		{
			*token = (*token)->next;
			break ;
		}
		else
			*token = (*token)->next;
	}
}

t_msh	*parsing(t_token *token)
{
	t_msh	*msh;
	t_msh	*new;
	int		i;

	msh = NULL;
	i = -1;
	while (token)
	{
		new = create_msh(++i);
		fill_msh(new, &token);
		msh_add_back(&msh, new);
	}
	return (msh);
}

/*
int	main(void)
{
	t_token	*token;
	t_msh	*msh;
	t_msh	*start;


	token = lexing("< infile \"ls\" |'cat -e' Makefile > outfile | echo hello");
	//token = lexing("cat -e | ls");
	msh = parsing(token);
	free_token(&token);
	start = msh;
	while (msh)
	{
		printf("index: %d\n", msh->index);
		if (msh->cmd)
		{
			int	i = -1;
			while (msh->cmd[++i])
				printf("cmd[%d]: %s\n", i, msh->cmd[i]);
		}
		if (msh->infile)
			printf("infile: %s\n", msh->infile);
		if (msh->outfile)
			printf("outfile: %s\n", msh->outfile);
		msh = msh->next;
	}
	free_msh(&start);
	return (0);
}*/
