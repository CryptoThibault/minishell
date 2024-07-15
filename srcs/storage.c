/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:06:46 by tchalaou          #+#    #+#             */
/*   Updated: 2024/07/15 17:50:25 by tchalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*create_var(char *key, char *value)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	var->key = ft_strdup(key);
	var->value = ft_strdup(value);
	var->next = NULL;
	return (var);
}

void	update_var(t_var *var, char *key, char *value)
{
	while (var && ft_strncmp(var->key, key, ft_strlen(key)))
		var = var->next;
	if (var)
	{
		free(var->value);
		var->value = ft_strdup(value);
	}
}

int	check_var(t_var *var, char *key)
{
	while (var)
	{
		if (!ft_strncmp(var->key, key, ft_strlen(key)))
			return (1);
		var = var->next;
	}
	return (0);
}

void	varadd_back(t_var **var, t_var *new)
{
	if (!new)
		return ;
	if (!*var)
		*var = new;
	else
	{
		while (*var)
			var = &(*var)->next;
		*var = new;
	}
}

void	set_var(t_var **var, char *key, char *value)
{
	if (check_var(*var, key))
		update_var(*var, key, value);
	else
		varadd_back(var, create_var(key, value));
}

void	free_var(t_var **var)
{
	t_var	*current;

	while (*var)
	{
		current = *var;
		*var = current->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		free(current);
	}
}
/*
int	main(void)
{
	t_var	*var;
	t_var	*start;

	var = NULL;
	set_var(&var, "test1_key", "");
	set_var(&var, "test2_key", "test2_value");
	set_var(&var, "test3_key", "test3_value");
	set_var(&var, "test2_key", "test2_update");
	start = var;
	while (var)
	{
		printf("%s=%s\n", var->key, var->value);
		var = var->next;
	}
	free_var(&start);
	return(0);
} */
