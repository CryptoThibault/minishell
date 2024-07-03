/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:14:30 by tchalaou          #+#    #+#             */
/*   Updated: 2024/07/02 15:50:25 by tchalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	t_token	*token;
	t_msh	*msh;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
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
		token = lexing(line);
		free(line);
		msh = parsing(token);
		free_token(&token);
		execute(msh);
		free_msh(&msh);
	}
	return (0);
}
