/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:10:58 by vados-sa          #+#    #+#             */
/*   Updated: 2024/08/19 16:45:22 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* int	exec(t_data*data)
{
	int		qt_cmd;
	int		**fds;
	pid_t	*id_p;

	qt_cmd = ft_lstsize_mod(data->command);
	fds = create_pipes(qt_cmd);
	if (!fds)
		return (EXIT_FAIL);
	id_p = (pid_t *)ft_calloc((qt_cmd - 1), sizeof(pid_t));
	if (!id_p)
		return (EXIT_FAIL);
	//execution
	//free
	return (EXIT_SUCC);
}

int	**create_pipes(int qt_cmd)
{
	int	**fds;
	int	i;

	if (!qt_cmd)
		return (NULL);
	fds = (int **)malloc(((qt_cmd - 1) * sizeof(int *)));
	if (!fds)
	{
		//print error
		return (NULL);
	}
	i = 0;
	while (i < qt_cmd - 1)
	{
		fds[i] = (int *)ft_calloc(2, sizeof(int));
		if (!fds[i])
		{
			//print error
			return (NULL);
		}
		if (pipe(fds[i]) == -1)
		{
			//print error
			return (NULL);
		}
		i++;
	}
	return (fds);
}

int	processing(int **fds, pid_t *id_p, t_data *data)
{
	t_command	*command;
	int			i;

	command = data->command;
	i = 0;
	while (command)
	{
		if (check_if_builtin(command))
		{
			if (process_builtin())
				return (EXIT_FAIL);
		}
		else
		{
			if (process_not_builtin())
				return (EXIT_FAIL);
		}
		i++;
		command = command->next;
	}
	//child_exec
	return (EXIT_SUCC);
} */

void	free_double_pointer(char**str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

char	*get_cmd_path(char*cmd, char**envp)
{
	char	**paths;
	char	*temp;
	char	*result;
	int		i;

	i = 0;
	while (ft_strncmp("PATH", envp[i], 4))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		result = ft_strjoin(temp, cmd);
		free(temp);
		if (access(result, F_OK | X_OK) == 0)
			return (result);
		free(result);
		i++;
	}
	free_double_pointer(paths);
	return (NULL);
}


void	close_fd(int*fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	execute_command(t_command *cmd, t_data *data)
{
	int		i;
	char	*cmd_path;

	i = 0;
	cmd_path = get_cmd_path(cmd->command, data->env);
	if (!cmd_path)
	{
		//error
	}
	if (execve(cmd_path, cmd, data->env) < 0)
		print_error("Error: Not possible to execute command\n");
}

void	simpler_child_process(int *fd, t_command *cmd, t_data *data)
{
	dup2(fd[1], STDOUT_FILENO);
	close_fd(fd);
	execute_command(cmd, data);
}

int	exec(t_data *data)
{
	t_command	*cmd;

	cmd = data->command;
	dup2(data->input_fd, STDIN_FILENO);
	close(data->input_fd);
	while (cmd)
	{
		if (cmd_is_builtin(cmd))
		{
			if (process_builtin(data, cmd))
				return (EXIT_FAIL);
		}
		else
		{
			if (process_not_builtin(data, cmd))
				return (EXIT_FAIL);
		}
		cmd = cmd->next;
	}
	dup2(data->output_fd, STDOUT_FILENO);
	close(data->output_fd);
	execute_command(cmd, data);
}

int	process_not_builtin(t_data *data, t_command *cmd)
{
	int		fd[2];
	pid_t	id_f;

	if (pipe(fd) < 0)
		;//print_error("Error: Problem ocurred with pipe\n");
	id_f = fork();
	if (id_f < 0)
		;//print_error("Error: Problem occur while forking\n");
	if (id_f == 0)
		simpler_child_process(fd, cmd, data);
	else
		waitpid(id_f, NULL, 0);
	dup2(fd[0], STDIN_FILENO);
	close_fd(fd);
}
