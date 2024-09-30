/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:55:02 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/30 13:19:13 by vados-sa         ###   ########.fr       */
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
