/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:46:13 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/07/23 14:46:35 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_data(t_data *data, char **env)
{
	init_env(data, env);
	init_path(data, env);
	data->exit_status = 0;
}

void	init_env(t_data *data, char **env)
{
	int i;

	i = 0;
	data->env = ft_calloc(ft_arrlen(env) + 1, sizeof(char *));
	if (!data->env)
		//free_and_exit
	while (env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (!data->env[i])
			//free_and_exit
		i++;
	}
	env[i] = NULL;	
}

void	init_path(t_data *data, char **env)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], "PATH=", 5))
		{
			data->path = ft_strdup(data->env[i]);
			if (!data->path)
				//free_and_exit
			return ;
		}
		i++;
	}
	//error_if_not_find_path
}
