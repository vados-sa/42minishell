/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:39:25 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/30 13:36:43 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	**create_pipes(int qt_cmd)
{
	int	**fds;
	int	i;

	if (!qt_cmd)
		return (NULL);
	fds = (int **)malloc(((qt_cmd - 1) * sizeof(int *)));
	if (!fds)
	{
		ft_putendl_fd("minishel: error with malloc pipes", 2);
		return (NULL);
	}
	i = 0;
	while (i < qt_cmd - 1)
	{
		fds[i] = (int *)ft_calloc(2, sizeof(int));
		if (!fds[i] || pipe(fds[i]) == -1)
		{
			ft_putendl_fd("minishel: error occured while piping", 2);
			free_double_pointer_int(fds, qt_cmd);
			return (NULL);
		}
		i++;
	}
	return (fds);
}

static int	redirect_input(int **fds, int pos, t_data *data)
{
	if (pos == 0)
	{
		if (dup2(data->input_fd, STDIN_FILENO) == -1)
		{
			close_fd(&data->input_fd);
			return (EXIT_FAIL);
		}
		close_fd(&data->input_fd);
	}
	else
	{
		if (dup2(fds[pos - 1][0], STDIN_FILENO) == -1)
		{
			close_fd(&fds[pos - 1][0]);
			return (EXIT_FAIL);
		}
		close_fd(&fds[pos - 1][0]);
	}
	return (EXIT_SUCC);
}

static int	redirect_output(int **fds, int pos, t_data *data, int cmds_num)
{
	if (pos == cmds_num - 1)
	{
		if (dup2(data->output_fd, STDOUT_FILENO) == -1)
		{
			close_fd(&data->output_fd);
			return (EXIT_FAIL);
		}
		close_fd(&data->output_fd);
	}
	else
	{
		if (dup2(fds[pos][1], STDOUT_FILENO) == -1)
		{
			close_fd(&fds[pos][1]);
			return (EXIT_FAIL);
		}
		close_fd(&fds[pos][1]);
	}
	return (EXIT_SUCC);
}

int	redirect_io(int **fds, int pos, t_data *data, int cmds_num)
{
	if (redirect_input(fds, pos, data) == EXIT_FAIL)
		return (EXIT_FAIL);
	if (redirect_output(fds, pos, data, cmds_num) == EXIT_FAIL)
		return (EXIT_FAIL);
	return (EXIT_SUCC);
}
