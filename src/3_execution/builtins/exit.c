/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 23:20:43 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/06 13:18:52 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	minishell_exit(t_data *data, int exit_code)
{
	char	*file;

	printf("exit\n\n");
	file = find_path("HISTFILE=", data->env);
	if (file)
		write_history(file + 9);
	free_data(data);
	free_env_and_path(data);
	clear_history();
	exit (exit_code);
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
	minishell_exit(data, EXIT_SUCC);
	return (EXIT_SUCC);
}
