/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:46:13 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/27 14:04:42 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	init_env(t_data *data, char **env)
{
	int	i;

	i = 0;
	data->env = ft_calloc(ft_arrlen(env) + 1, sizeof(char *));
	if (!data->env)
	{
		perror("Failed to allocate memory for environment variables");
		return (EXIT_FAIL);
	}
	while (env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (!data->env[i])
		{
			perror("Failed to duplicate environment variable");
			while (i > 0)
				free(data->env[--i]);
			free(data->env);
			return (EXIT_FAIL);
		}
		i++;
	}
	data->env[i] = NULL;
	return (EXIT_SUCC);
}

static int	init_path(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], "PATH=", 5))
		{
			data->path = ft_strdup(data->env[i]);
			if (!data->path)
				return (EXIT_FAIL);
		}
		i++;
	}
	if (!data->path)
	{
		perror("Failed to find PATH");
		return (EXIT_FAIL);
	}
	return (EXIT_SUCC);
}

static void	init_io(t_data *data)
{
	data->input_fd = STDIN_FILENO;
	data->input_value = NULL;
	data->input_type = STDIN;
	data->output_fd = STDOUT_FILENO;
	data->output_value = NULL;
	data->output_type = STDOUT;
}

int	init_data(t_data *data, char **env)
{
	int	i;

	i = 0;
	if (init_env(data, env))
		return (EXIT_FAIL);
	if (init_path(data))
	{
		while (data->env[i])
		{
			free(data->env[i]);
			data->env[i] = NULL;
			i++;
		}
		free(data->env);
		data->env = NULL;
		return (EXIT_FAIL);
	}
	init_io(data);
	data->exit_status = 0;
	return (EXIT_SUCC);
}
