/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:44:07 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/16 17:32:31 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


//code that chatgpt provided
int process_builtin(int **fds, int pos, t_command *cmd, t_data *data) {
    int fd[2];
    int exit_code;

    fd[0] = dup(STDIN_FILENO);
    fd[1] = dup(STDOUT_FILENO);
    if (fd[0] == -1 || fd[1] == -1)
        return (EXIT_FAIL);

    if (redirect_io(fds, pos, data, ft_lstsize_mod(data->command)) == EXIT_FAIL)
        return (EXIT_FAIL);

    exit_code = execute_builtin(cmd, data);  // Execute the built-in command

    if (dup2(fd[0], STDIN_FILENO) == -1 || dup2(fd[1], STDOUT_FILENO) == -1)
        return (EXIT_FAIL);

    close_fd(&fd[0]);
    close_fd(&fd[1]);

    data->exit_status = exit_code;
    return (exit_code);
}


/* int	process_builtin(int **fds, int pos, t_command *cmd, t_data *data)
{
	int	fd[2];
	int	exit_code;

	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	if (fd[0] == -1 || fd[1] == -1)
		return (EXIT_FAIL);
	if (redirect_io(fds, pos, data, ft_lstsize_mod(data->command)))
		return (EXIT_FAIL);
	//close_unused_fd(fds, pos, FD_RW, pos + 1);
	exit_code = execute_builtin(cmd, data);
	if (dup2(fd[0], STDIN_FILENO) == -1 || dup2(fd[1], STDOUT_FILENO) == -1)
		return (EXIT_FAIL);
	close_fd(&fd[0]);
	close_fd(&fd[1]);
	data->exit_status = exit_code;
	return (exit_code);
} */

int	execute_builtin(t_command *cmd, t_data *data)
{
	int	exit_code;

	if (!ft_strcmp(cmd->command, "echo"))
		exit_code = builtin_echo(cmd);
	else if (!ft_strcmp(cmd->command, "cd"))
		exit_code = builtin_cd(cmd, data);
	else if (!ft_strcmp(cmd->command, "pwd"))
		exit_code = builtin_pwd(cmd, data);
	else if (!ft_strcmp(cmd->command, "export"))
		exit_code = builtin_export(cmd, data);
	else if (!ft_strcmp(cmd->command, "unset"))
		exit_code = builtin_unset(cmd, data);
	else if (!ft_strcmp(cmd->command, "env"))
		exit_code = builtin_env(cmd, data);
	else
		exit_code = builtin_exit(cmd, data);
	return (exit_code);
}

int	check_if_builtin(t_command *cmd)
{
	if (!ft_strcmp(cmd->command, "cd") || \
		!ft_strcmp(cmd->command, "pwd") || \
		!ft_strcmp(cmd->command, "echo") || \
		!ft_strcmp(cmd->command, "exit") || \
		!ft_strcmp(cmd->command, "env") || \
		!ft_strcmp(cmd->command, "unset") || \
		!ft_strcmp(cmd->command, "export"))
		return (1);
	return (0);
}
