/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:32:26 by vados-sa          #+#    #+#             */
/*   Updated: 2024/09/30 13:33:18 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
