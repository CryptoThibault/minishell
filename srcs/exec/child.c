/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:33:48 by wnocchi           #+#    #+#             */
/*   Updated: 2024/08/15 08:39:55 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_flags(t_msh *msh)
{
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (msh->append == true)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	return (flags);
}

int	close_files(t_msh *msh)
{
	if (msh->in != -1)
		close(msh->in);
	if (msh->out != -1)
		close(msh->out);
	if (msh->pipefd[0] != -1)
		close(msh->pipefd[0]);
	if (msh->pipefd[1] != -1)
		close(msh->pipefd[1]);
	return (0);
}

int	close_pipes(t_msh *msh)
{
	t_msh	*current;

	current = ft_lastnode(msh);
	while (current)
	{
		if (current->pipefd[0] != -1)
			close(current->pipefd[0]);
		if (current->pipefd[1] != -1)
			close(current->pipefd[1]);
		close_files(current);
		current = current->prev;
	}
	return (0);
}

int	dup_in_fd(t_msh *msh)
{
	if (msh->infile)
	{
		msh->in = open(msh->infile, O_RDONLY, 0644);
		if (msh->in != -1)
		{
			if (dup2(msh->in, STDIN_FILENO) == -1)
				return (perror("msh"), close_pipes(msh), close_files(msh), 1);
		}
		else
			return (perror("msh"), close_pipes(msh), close_files(msh), 1);
	}
	if (msh->outfile != NULL)
	{
		msh->out = open(msh->outfile, get_flags(msh), 0644);
		if (msh->out != -1)
		{
			if (dup2(msh->out, STDOUT_FILENO) == -1)
				return (perror("msh"), close_pipes(msh), close_files(msh), 1);
		}
		else
			return (perror("msh"), close_pipes(msh), close_files(msh), 1);
	}
	return (0);
}

int	redirect_fd(t_msh *msh)
{
	if (msh->index != 1 && msh->infile == NULL)
	{
		if (dup2(msh->prev->pipefd[0], STDIN_FILENO) == -1)
			return (close_pipes(msh), 1);
	}
	if (msh->next != NULL && msh->outfile == NULL)
	{
		if (dup2(msh->pipefd[1], STDOUT_FILENO) == -1)
			return (close_pipes(msh), 1);
	}
	if (dup_in_fd(msh))
		return (close_files(msh), 1);
	if (msh->here_doc == 1)
		unlink(msh->infile);
	close_pipes(msh);
	return (0);
}
