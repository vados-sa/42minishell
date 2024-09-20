/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 23:20:43 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/20 12:25:42 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	minishell_exit(t_data *data, int exit_code, int flag)
{
	char	*file;

	if (!flag)
		printf("exit\n");
	if (data->saved_stdin >= 0)
		close_fd(&data->saved_stdin);
	if (data->saved_stdout >= 0)
		close_fd(&data->saved_stdout);
	file = find_path("HISTFILE=", data);
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
		//printf("Argument: %s\n", cmd->flags->content);
		if (!ft_isnumeric(cmd->flags->content) || cmd->flags->next)
		{
			ft_putstr_fd("minishell: exit does not support options\n", 2);
			return (EXIT_FAIL);
		}
		minishell_exit(data, ft_atoi(cmd->flags->content), 0);
	}
	if (cmd->arguments)
	{
		//printf("Argument: %s\n", cmd->arguments->content);
		if (cmd->arguments->next)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (EXIT_FAIL);
		}
		if (!ft_isnumeric(cmd->arguments->content))
		{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(cmd->arguments->content, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			minishell_exit(data, 2, 1);
		}
		minishell_exit(data, ft_atoi(cmd->arguments->content), 0);
	}
	minishell_exit(data, EXIT_SUCC, 0);
	return (EXIT_SUCC);
}
