/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 18:36:40 by vados-sa          #+#    #+#             */
/*   Updated: 2024/10/05 19:41:51 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_fd(t_data *data, int fd)
{
	t_fd_node	*new_node;

	new_node = malloc(sizeof(t_fd_node));
	if (!new_node)
		return (EXIT_FAIL);
	new_node->fd = fd;
	new_node->next = data->open_fds;
	data->open_fds = new_node;
	return (EXIT_SUCCESS);
}

void	remove_fd(t_data *data, int fd)
{
	t_fd_node	*current;
	t_fd_node	*prev;

	current = data->open_fds;
	prev = NULL;
	while (current)
	{
		if (current->fd == fd)
		{
			if (prev)
				prev->next = current->next;
			else
				data->open_fds = current->next;
			close(fd);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	close_all_fds(t_data *data)
{
	t_fd_node	*current;
	t_fd_node	*next;

	current = data->open_fds;
	next = NULL;
	while (current)
	{
		close(current->fd);
		next = current->next;
		free(current);
		current = next;
	}
	data->open_fds = NULL;
}

void	write_line_to_fd(int *fd1, char *line)
{
	write(*fd1, line, ft_strlen(line));
	write(*fd1, "\n", 1);
	free(line);
}

void	exit_cleanup(t_data *data, int *fd1, int exit_code)
{
	free_data(data);
	free_env_and_path(data);
	close(*fd1);
	exit(exit_code);
}
