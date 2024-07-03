/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:02:41 by tchalaou          #+#    #+#             */
/*   Updated: 2024/07/02 16:22:56 by tchalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_msh	*create_msh(int index)
{
	t_msh	*msh;

	msh = malloc(sizeof(t_msh));
	if (!msh)
		return (NULL);
	msh->index = index;
	msh->cmd = NULL;
	msh->infile = NULL;
	msh->outfile = NULL;
	msh->here_doc = 0;
	msh->append = 0;
	msh->in_fd = -1;
	msh->out_fd = -1;
	msh->next = NULL;
	msh->prev = NULL;
	return (msh);
}

int	count_words(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->id == WORD)
	{
		count++;
		token = token->next;
	}
	return (count);
}

void	fill_command(t_msh *msh, t_token **token)
{
	int	i;
	
	msh->cmd = malloc(sizeof(char *) * count_words(*token));
	if (!msh->cmd)
		return ;
	i = -1;
	while (*token && (*token)->id == WORD)
	{
		msh->cmd[++i] = ft_strdup((*token)->word);
		*token = (*token)->next;
	}
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
		msh->infile = ft_strdup((*token)->word);
	*token = (*token)->next;
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
		msh->outfile = ft_strdup((*token)->word);
	*token = (*token)->next;
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

t_msh	*mshget_last(t_msh *msh)
{
	t_msh	*current;

	if (!msh)
		return (0);
	current = msh;
	while (current->next)
		current = current->next;
	return (current);
}

void	mshadd_back(t_msh **msh, t_msh *new)
{
	t_msh	*last;

	if (!new)
		return ;
	if (!*msh)
		*msh = new;
	else
	{
		last = mshget_last(*msh);
		last->next = new;
		new->prev = last;
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
		mshadd_back(&msh, new);
	}
	return (msh);
}

void	free_msh(t_msh **msh)
{
	t_msh	*current;

	while (*msh)
	{
		current = *msh;
		*msh = current->next;
		if (current->cmd)
			free_array(current->cmd);
		if (current->infile)
			free(current->infile);
		if (current->outfile)
			free(current->outfile);
		free(current);
	}
}

int	main(void)
{
	t_token	*token;
	t_msh	*msh;
	t_msh	*start;


	token = lexing("< infile ls | cat -e > outfile | echo hello");
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
			while (msh->cmd && msh->cmd[++i])
				printf("cmd[%d]: %s\n", i, msh->cmd[i]);
			if (msh->infile)
				printf("infile: %s\n", msh->infile);
			if (msh->outfile)
				printf("outfile: %s\n", msh->outfile);
		}
		msh = msh->next;
	}
	free_msh(&start);
	return (0);
}
