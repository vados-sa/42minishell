/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:55:02 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/30 14:55:00 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_error_code(char *message, char tkn, int exit_code)
{
	printf("%s'%c'\n", message, tkn);
	return (exit_code);
}

int	perror_return_error(char *message)
{
	perror(message);
	return (EXIT_FAIL);
}

void	pe_status(t_data *data, char *cmd, char *message, int status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(message, 2);
	data->exit_status = status;
}
