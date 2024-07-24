/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_msh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:33:18 by tchalaou          #+#    #+#             */
/*   Updated: 2024/07/24 18:08:02 by tchalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexing(char *line, t_env *env)
{
	t_token	*token;
	t_token	*add;
	int		i;

	token = NULL;
	i = -1;
	while (line[++i])
	{
		add = create_token(env);
		fill_token(add, line, &i);
		token_add_back(&token, add);
	}
	return (token);
}

t_msh	*parsing(t_token *token, t_env *env)
{
	t_msh	*msh;
	t_msh	*add;
	int		i;

	msh = NULL;
	i = -1;
	while (token)
	{
		add = create_msh(++i, env);
		if (!add)
			return (NULL);
		fill_msh(add, &token);
		if (!add->cmd)
		{
			free_msh(&msh);
			return (NULL);
		}
		msh_add_back(&msh, add);
	}
	return (msh);
}

t_msh	*get_msh(char *line, t_env *env)
{
	t_token	*token;
	t_msh	*msh;

	token = lexing(line, env);
	free(line);
	if (!token)
		return (NULL);
	msh = parsing(token, env);
	free_token(&token);
	return (msh);
}