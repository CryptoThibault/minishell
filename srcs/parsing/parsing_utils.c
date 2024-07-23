/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:24:26 by tchalaou          #+#    #+#             */
/*   Updated: 2024/07/23 15:59:46 by tchalaou         ###   ########.fr       */
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
	msh->heredoc = 0;
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

t_msh	*msh_get_last(t_msh *msh)
{
	t_msh	*current;

	if (!msh)
		return (0);
	current = msh;
	while (current->next)
		current = current->next;
	return (current);
}

void	msh_add_back(t_msh **msh, t_msh *new)
{
	t_msh	*last;

	if (!new)
		return ;
	if (!*msh)
		*msh = new;
	else
	{
		last = msh_get_last(*msh);
		last->next = new;
		new->prev = last;
	}
}

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
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
