/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 23:20:43 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/26 18:15:34 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	minishell_exit(t_data *data, int exit_code, int flag)
{
	char	*file;

	if (!flag)
		ft_putstr_fd("exit\n", 2);
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

static int	check_exit_flags(t_command *cmd)
{
	if (cmd->flags)
	{
		if (!ft_isnumeric(cmd->flags->content) || cmd->flags->next)
		{
			ft_putstr_fd("minishell: exit does not support options\n", 2);
			return (EXIT_FAIL);
		}
		return (ft_atoi(cmd->flags->content));
	}
	return (-1);
}

static int	check_exit_arguments(t_command *cmd, t_data *data)
{
	if (cmd->arguments)
	{
		if (cmd->arguments->next)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (EXIT_FAIL);
		}
		remove_possible_quotes(cmd->arguments->content);
		if (!ft_isnumeric(cmd->arguments->content))
		{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(cmd->arguments->content, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			minishell_exit(data, 2, 1);
		}
		return (ft_atoi(cmd->arguments->content));
	}
	return (-1);
}

int	builtin_exit(t_command *cmd, t_data *data)
{
	int	exit_code;

	exit_code = check_exit_flags(cmd);
	if (exit_code != -1)
		minishell_exit(data, exit_code, 0);
	exit_code = check_exit_arguments(cmd, data);
	if (exit_code != -1)
		minishell_exit(data, exit_code, 0);
	minishell_exit(data, EXIT_SUCC, 0);
	return (EXIT_SUCC);
}
