/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_msh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:42:48 by tchalaou          #+#    #+#             */
/*   Updated: 2024/07/24 18:07:50 by tchalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_command(t_msh *msh, t_token **token)
{
	int	i;

	msh->cmd = ft_calloc(sizeof(char *), (count_words(*token) + 1));
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
	if (!*token)
	{
		printf("msh: parsing error\n");
		return ;
	}
	if ((*token)->id == SMALLER)
	{
		*token = (*token)->next;
		msh->here_doc = 1;
	}
	if (!*token)
	{
		printf("msh: parsing error\n");
		return ;
	}
	if ((*token)->id == WORD)
		msh->infile = ft_strdup((*token)->word);
	else
		printf("msh: parsing error\n");
	*token = (*token)->next;
}

void	fill_bigger(t_msh *msh, t_token **token)
{
	*token = (*token)->next;
	if (!*token)
	{
		printf("msh: parsing error\n");
		return ;
	}
	if ((*token)->id == BIGGER)
	{
		*token = (*token)->next;
		msh->append = 1;
	}
	if (!*token)
	{
		printf("msh: parsing error\n");
		return ;
	}
	if ((*token)->id == WORD)
		msh->outfile = ft_strdup((*token)->word);
	else
		printf("msh: parsing error\n");
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
