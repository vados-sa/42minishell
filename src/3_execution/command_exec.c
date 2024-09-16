/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:41:00 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/14 19:39:06 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_not_builtin(int **fds, int pos, int *pid, t_data *data)
{
	t_command	*cmd;
	int			i;

	i = 0;
	cmd = data->command;
	while (cmd && i < pos)
	{
		cmd = cmd->next;
		i++;
	}
	*pid = fork();
	if (*pid < 0)
		return (EXIT_FAIL);
	if (*pid == 0)
	{
		if (redirect_io(fds, pos, data, ft_lstsize_mod(data->command)))
			return (EXIT_FAIL);
		close_unused_fd(fds, pos, FD_RW, ft_lstsize_mod(data->command));
		execute_command(cmd, data);
		return (EXIT_SUCC);
	}
	return (EXIT_SUCC);
}

void	execute_command(t_command *cmd, t_data *data)
{
	char	*path;

	if (!cmd || !cmd->command)
		exit (EXIT_FAIL);
	path = NULL;
	if (access(cmd->command, X_OK | F_OK) == 0)
		data->exit_status = execve(cmd->command, cmd->final_av, data->env);
	else
	{
		if (data->env)
			path = get_cmd_path(cmd, data->env);
	}
	if (path)
		data->exit_status = execve(path, cmd->final_av, data->env);
	else
		data->exit_status = 127;
	free (path);
	exit (data->exit_status);
}

static char	*join_paths_and_command(char *path, char *command)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, command);
	free(temp);
	return (result);
}

static char	**get_paths(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	while (ft_strncmp("PATH", env[i], 4))
		i++;
	paths = ft_split(env[i] + 5, ':');
	return (paths);
}

char	*get_cmd_path(t_command *cmd, char **env)
{
	char	**paths;
	char	*result;
	int		i;

	paths = get_paths(env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		result = join_paths_and_command(paths[i], cmd->command);
		if (result && access(result, F_OK | X_OK) == 0)
		{
			free_double_pointer_char(paths);
			return (result);
		}
		free(result);
		i++;
	}
	free_double_pointer_char(paths);
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(cmd->command, 2);
	return (NULL);
}

/* char	*get_cmd_path(t_command *cmd, char**env)
{
	char	**paths;
	char	*temp;
	char	*result;
	int		i;

	i = 0;
	while (ft_strncmp("PATH", env[i], 4))
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		result = ft_strjoin(temp, cmd->command);
		free(temp);
		if (access(result, F_OK | X_OK) == 0)
			return (result);
		free(result);
		i++;
	}
	free_double_pointer(paths);
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(cmd->command, 2);
	return (NULL);
} */
