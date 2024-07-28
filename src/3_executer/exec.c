/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:10:58 by vados-sa          #+#    #+#             */
/*   Updated: 2024/07/27 20:49:55 by mrabelo-         ###   ########.fr       */
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
	if (!check_redirections(data))
		return (EXIT_FAIL);
	id_p = (pid_t *)ft_calloc(qt_cmd, sizeof(pid_t));
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

int	check_redirections(t_data*data)
{
	//check here_doc and open it
	//check input and open it
	//check input without nothing
	//check output and if is append mode
	//check output normal
	//check output without nothing
	//check errors
	return (EXIT_SUCC);
}
