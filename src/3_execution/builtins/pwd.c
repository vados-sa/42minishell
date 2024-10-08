/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 23:20:43 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/10/08 15:54:06 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	builtin_pwd(t_command *cmd, t_data *data)
{
	int	i;

	i = 0;
	if (cmd->arguments || cmd->flags)
	{
		ft_putstr_fd("pwd doesn't support options\n", STDERR_FILENO);
		return (EXIT_FAIL);
	}
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], "PWD=", 4))
		{
			ft_putstr_fd(&data->env[i][4], 1);
			write(1, "\n", 1);
			return (EXIT_SUCC);
		}
		i++;
	}
	ft_putstr_fd("minishell: pwd not found in env\n", 2);
	return (EXIT_FAIL);
}
