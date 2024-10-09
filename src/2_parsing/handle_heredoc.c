/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:23:31 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/10/09 18:02:41 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	eof_error(char *limiter, int line_num)
{
	char	*nb;

	nb = ft_itoa(line_num);
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putstr_fd(nb, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putstr_fd("')\n", 2);
	free(nb);
}

void	get_all_file(int *fd1, char *limiter, t_data *data)
{
	char	*line;
	int		line_num;

	line_num = 0;
	signals_heredoc_handler();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (g_exit_status == SIGINT)
				exit_cleanup(data, fd1, 130);
			eof_error(limiter, line_num);
			break ;
		}
		line_num++;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && \
			ft_strlen(line) == ft_strlen(limiter))
		{
			free(line);
			break ;
		}
		write_line_to_fd(fd1, line, data);
	}
	close(*fd1);
}

int	heredoc_child_process(t_data *data, int *fd)
{
	remove_fd(data, fd[0]);
	get_all_file(&fd[1], data->input_value, data);
	free_data(data);
	free_env_and_path(data);
	exit(EXIT_SUCCESS);
}

int	heredoc_parent_process(t_data *data, int *fd, int status)
{
	signals_parent_heredoc_handler();
	waitpid(-1, &status, 0);
	remove_fd(data, fd[1]);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		remove_fd(data, fd[0]);
		data->exit_status = 130;
		return (EXIT_FAIL);
	}
	data->input_fd = fd[0];
	return (EXIT_SUCC);
}

int	handle_heredoc(t_data *data)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	status = 0;
	if (pipe(fd) < 0)
		return (perror_return_error("heredoc pipe"));
	if (add_fd(data, fd[0]) || add_fd(data, fd[1]))
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		return (perror_return_error("fork failed"));
	else if (pid == 0)
		heredoc_child_process(data, fd);
	else
		return (heredoc_parent_process(data, fd, status));
	return (EXIT_FAIL);
}
