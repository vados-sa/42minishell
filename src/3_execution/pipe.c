/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:39:25 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/06 15:51:02 by mrabelo-         ###   ########.fr       */
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
			free_double_pointer_int(fds);
			return (NULL);
		}
		i++;
	}
	return (fds);
}

void	close_fd(int *fd)
{
	if (!fd || *fd <= 2)
		return ;
	if (close(*fd) == -1)
	{
		ft_putendl_fd("minishell: error while closing fd", 2);
		return ;
	}
	*fd = -1;
}

void	close_unused_fd(int **fds, int pos, int keep, int cmds_num)
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

int	redirect_io(int **fds, int pos, t_data *data, int cmds_num)
{
	if (pos == 0)
	{
		if (dup2(data->input_fd, STDIN_FILENO) == -1)
			return (EXIT_FAIL);
		close_fd(&data->input_fd);
	}
	else
	{
		if (dup2(fds[pos - 1][0], STDIN_FILENO) == -1)
			return (EXIT_FAIL);
		close_fd(&fds[pos - 1][0]);
	}
	if (pos == cmds_num - 1)
	{
		if (dup2(data->output_fd, STDOUT_FILENO) == -1)
			return (EXIT_FAIL);
		close_fd(&data->output_fd);
	}
	else
	{
		if (dup2(fds[pos][1], STDOUT_FILENO) == -1)
			return (EXIT_FAIL);
		close_fd(&fds[pos][1]);
	}
	return (EXIT_SUCC);
}
