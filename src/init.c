/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:46:13 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/06 14:20:30 by mrabelo-         ###   ########.fr       */
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

static void	init_histfile(t_data *data)
{
	char	*home_path;
	char	*histfile_path;

	home_path = find_path("HOME=", data->env);
	if (!home_path)
		printf("Warning: HOME environment variable not set. \
				History will not be saved.\n");
	else
	{
		histfile_path = ft_strjoin(home_path + 5, "/.minishell_history");
		if (histfile_path)
		{
			add_value_to_env("HISTFILE=", histfile_path, data);
			read_history(histfile_path);
			free(histfile_path);
			histfile_path = NULL;
		}
		free(home_path);
		home_path = NULL;
	}
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
			i++;
		}
		free(data->env);
		return (EXIT_FAIL);
	}
	init_histfile(data);
	init_io(data);
	data->exit_status = 0;
	return (EXIT_SUCC);
}
