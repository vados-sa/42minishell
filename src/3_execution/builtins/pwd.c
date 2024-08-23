/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 23:20:43 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/08/23 23:54:35 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	builtin_pwd(t_command *cmd, t_data *data)
{
	int	i;

	i = 0;
	if (cmd->flags)
	{
		ft_putstr_fd("minishell: pwd does not support options", 1); //check if needs a new line at the end, also check if it is 1 or 2
		return (EXIT_FAIL);
	}
	if (cmd->arguments)
	{
		ft_putstr_fd("minishell: pwd does not support argument", 1); //check if needs a new line at the end, also check if it is 1 or 2
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
	ft_putstr_fd("minishell: pwd not found in env", 1); //check if needs a new line at the end, also check if it is 1 or 2
	return (EXIT_FAIL);
}
