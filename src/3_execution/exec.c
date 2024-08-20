/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:10:58 by vados-sa          #+#    #+#             */
/*   Updated: 2024/08/20 17:20:58 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec(t_data*data)
{
	int		qt_cmd;
	int		**fds;
	pid_t	*id_p;

	qt_cmd = ft_lstsize_mod(data->command);
	fds = create_pipes(qt_cmd);
	if (!fds)
		return (EXIT_FAIL);
	id_p = (pid_t *)ft_calloc((qt_cmd), sizeof(pid_t));
	if (!id_p)
		return (EXIT_FAIL);
	processing(fds, id_p, data);
	//free pipes
	free (id_p);
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
		if (!fds[i] || pipe(fds[i]) < 0)
		{
			//print error
			//free fds
			return (NULL);
		}
		i++;
	}
	return (fds);
}

int	check_if_builtin(t_command *command)
{
	if (ft_strcmp(command, "cd") || \
		ft_strcmp(command, "pwd") || \
		ft_strcmp(command, "echo") || \
		ft_strcmp(command, "exit") || \
		ft_strcmp(command, "env") || \
		ft_strcmp(command, "unset") || \
		ft_strcmp(command, "export"))
		return (0);
	return (1);
}

t_command	*set_correct_cmd(t_command *command, int pos)
{
	int	i;

	i = 0;
	while (command && i <= pos)
	{
		command = command->next;
		i++;
	}
	return (command);
}

void	close_fd(int *fd) //check function
{
	if (*fd <= 2)
		return ;
	close(*fd);
	*fd = -1;
}

void	close_unused_fd(int **fds, int pos, int keep, int cmds_num) //check function
{
	int	i;

	if (!fds || pos < 0 || cmds_num < 1 || keep > FD_RW || keep < FD_E)
		return ;
	i = 0;
	while (i < cmds_num - 1)
	{
		if (i != pos - 1)
			close_fd(&fds[i][0]);
		if (i != pos)
			close_fd(&fds[i][1]);
		i++;
	}
	if (keep != FD_R && pos < cmds_num - 1)
		close_fd(&fds[pos][0]);
	if (keep != FD_W && pos < cmds_num - 1)
		close_fd(&fds[pos][1]);
}

int	process_not_builtin(int **fds, int pos, int *pid, t_data *data)
{
	t_command	*cmd;

	cmd = set_correct_cmd(data->command, pos);
	*pid = fork();
	if (*pid < 0)
		return (EXIT_FAIL);
	if (*pid == 0)
	{
		if (pos == 0)
			dup2(data->input_fd, STDIN_FILENO);
		else
			dup2(fds[pos - 1][0], STDIN_FILENO);
		if (pos == (ft_lstsize_mod(data->command) - 1))
			dup2(data->output_fd, STDOUT_FILENO);
		else
			dup2(fds[pos][1], STDOUT_FILENO);
		close_unused_fd(fds, pos, FD_RW, ft_lstsize_mod(data->command));
		exit (command_executer(cmd, data));
	}
	close_fd(&fds[pos][0]);
	close_fd(&fds[pos][1]);
	return (EXIT_FAIL);
}

int	processing(int **fds, pid_t *id_p, t_data *data)
{
	t_command	*command;
	int			i;

	if (!fds || !id_p || !data)
		return (EXIT_FAIL); //check necessity
	command = data->command;
	i = 0;
	while (command)
	{
		if (check_if_builtin(command))
		{
			if (process_builtin(fds, i, command, data))
				return (EXIT_FAIL);
		}
		else
		{
			if (process_not_builtin(fds, i, &id_p[i], data))
				return (EXIT_FAIL);
		}
		i++;
		command = command->next;
	}
	//child_exec
	return (EXIT_SUCC);
}

process_builtin
command_executer
free
child_exec
print errors
