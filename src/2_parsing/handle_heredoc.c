/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:23:31 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/10/01 17:45:12 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	eof_error(char *limiter, int line_num)
{
	char *nb;

	nb = ft_itoa(line_num);
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putstr_fd(nb, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putstr_fd("')\n", 2);
	free(nb);
}

void	get_all_file(int fd1, char *limiter)
{
	char	*line;
	int		line_num;

	line_num = 0;
	while (1)
	{
		signals_heredoc_handler();
		line = readline("> ");
		if (!line)
    	{
        	eof_error(limiter, line_num);
        	exit(EXIT_SUCCESS);
    	}
		line_num++;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && \
			ft_strlen(line) == ft_strlen(limiter))
		{
			free(line);
			break ;
		}
		write(fd1, line, ft_strlen(line));
		write(fd1, "\n", 1);
		free(line);
	}
	close(fd1);
}

int	handle_heredoc(t_data *data)
{
	int fd[2];
    pid_t pid;
    int status;

    if (pipe(fd) < 0)
        return (perror_return_error("heredoc pipe"));
    pid = fork();
    if (pid == -1)
        return (perror_return_error("heredoc fork failed"));
    else if (pid == 0)
    {
        close(fd[0]);
        get_all_file(fd[1], data->input_value);
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(fd[1]);
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
            return (EXIT_FAILURE);
        data->input_fd = fd[0];
        return (EXIT_SUCC);
    }
}
