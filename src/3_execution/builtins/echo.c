/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 23:20:43 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/19 12:42:45 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	builtin_echo(t_command *cmd)
{
	t_list	*temp;

	if (cmd->flags && (cmd->flags->next || \
						ft_strcmp(cmd->flags->content, "-n")))
	{
		ft_putstr_fd("minishell: cd only supports '-n' flag\n", 2);
		return (EXIT_FAIL);
	}
	temp = cmd->arguments;
	while (temp)
	{
		ft_putstr_fd(temp->content, 1);
		if (temp->next)
			ft_putstr_fd(" ", 1);
		temp = temp->next;
	}
	if (!cmd->flags)
		ft_putstr_fd("\n", 1);
	return (EXIT_SUCC);
}
