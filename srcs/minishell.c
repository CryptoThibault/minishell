/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:14:30 by tchalaou          #+#    #+#             */
/*   Updated: 2024/07/15 17:48:58 by tchalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	t_env	*env;
	t_token *token;
	t_msh	*msh;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	env = get_env();
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (!ft_strlen(line))
			continue ;
		add_history(line);
		token = lexing(line, env);
		free(line);
		if (!token)
			continue ;
		msh = parsing(token);
		free_token(&token);
		if (!msh)
			continue ;
		execute(msh);
		free_msh(&msh);
	}
	free_env(&env);
	return (0);
}
