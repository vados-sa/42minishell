/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:46:13 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/08/06 13:29:44 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_data(t_data *data, char **env)
{
	if (init_env(data, env) || init_path(data, env))
		return (EXIT_FAIL);
	//DO SOMETHING ABOUT HISTORY
	data->input_fd = STDIN_FILENO;
	data->input_value = NULL;
	data->input_type = STDIN;
	data->output_fd = STDOUT_FILENO;
	data->output_value = NULL;
	data->output_type = STDOUT;
	data->exit_status = 0;
	return (EXIT_SUCC);
}

int	init_env(t_data *data, char **env)
{
	int	i;

	i = 0;
	data->env = ft_calloc(ft_arrlen(env) + 1, sizeof(char *));
	if (!data->env)
		;//free_and_exit(fail)
	while (env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (!data->env[i])
			;//free_and_exit(fail)
		i++;
	}
	env[i] = NULL;
	return (EXIT_SUCC);
}

int	init_path(t_data *data, char **env)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], "PATH=", 5))
		{
			data->path = ft_strdup(data->env[i]);
			if (!data->path)
				;//free_and_exit(fail)
			return (EXIT_FAIL);
		}
		i++;
	}
	//error_if_not_find_path
	return (EXIT_SUCC);
}
