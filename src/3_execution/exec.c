/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:10:58 by vados-sa          #+#    #+#             */
/*   Updated: 2024/10/09 11:46:30 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec(t_data*data)
{
	int		qt_cmd;

	qt_cmd = ft_lstsize_mod(data->command);
	data->fds = create_pipes(qt_cmd);
	if (!data->fds)
		return (EXIT_FAIL);
	data->id_p = (pid_t *)ft_calloc((qt_cmd), sizeof(pid_t));
	if (!data->id_p)
		return (EXIT_FAIL);
	processing(data);
	free_double_pointer_int(data->fds, qt_cmd);
	free(data->id_p);
	return (EXIT_SUCC);
}

static void	close_all_pipes(int **fds, int cmds_num)
{
	int	i;

	i = 0;
	while (i < cmds_num - 1)
	{
		close_fd(&fds[i][0]);
		close_fd(&fds[i][1]);
		i++;
	}
}

void	parent_exec(int pos, t_data *data)
{
	int	i;
	int	exit_code;

	if (!data->id_p || pos <= 0 || !data || !data->fds)
		return ;
	i = 0;
	while (i < pos)
	{
		if (data->id_p[i] > 0)
		{
			waitpid(data->id_p[i], &exit_code, 0);
			if (i == pos - 1)
			{
				if (WIFEXITED(exit_code))
					data->exit_status = WEXITSTATUS(exit_code);
				else if (WIFSIGNALED(exit_code))
					data->exit_status = WTERMSIG(exit_code) + 128;
				else
					data->exit_status = -1;
			}
		}
		i++;
	}
}

static int	process_commands(t_data *data)
{
	t_command	*command;
	int			i;

	command = data->command;
	i = 0;
	while (command)
	{
		if (check_if_builtin(command))
		{
			if (process_builtin(i, command, data))
				return (EXIT_FAIL);
		}
		else
		{
			if (process_not_builtin(i, data))
				return (EXIT_FAIL);
		}
		i++;
		command = command->next;
	}
	return (EXIT_SUCC);
}

int	processing(t_data *data)
{
	int	cmds_num;

	if (!data->fds || !data->id_p || !data)
		return (EXIT_FAIL);
	cmds_num = ft_lstsize_mod(data->command);
	if (process_commands(data) == EXIT_FAIL)
		return (EXIT_FAIL);
	close_all_pipes(data->fds, cmds_num);
	parent_exec(cmds_num, data);
	return (EXIT_SUCC);
}
