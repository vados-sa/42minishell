/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 23:20:43 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/08/31 15:42:57 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	minishell_exit(t_data *data, int exit_code)
{
	
}

int	builtin_exit(t_command *cmd, t_data*data)
{
	if (cmd->flags)
	{
		ft_putstr_fd("minishell: exit does not support options\n", 1); //check if it is 1 or 2
		return (EXIT_FAIL);
	}
	if (cmd->arguments)
	{
		if (cmd->arguments->next)
		{
			ft_putstr_fd("minishell: exit with too much arguments\n", 1); //check if it is 1 or 2
			return (EXIT_FAIL);
		}
		if (!ft_isnumeric(cmd->arguments->content))
		{
			ft_putstr_fd("minishell: exit argument must be numeric\n", 1); //check if it is 1 or 2
			return (EXIT_FAIL);
		}
		minishell_exit(data, ft_atoi(cmd->arguments->content));
	}
	minishell_exit(data, EXIT_SUCCESS);
}
