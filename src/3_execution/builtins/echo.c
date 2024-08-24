/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 23:20:43 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/08/24 20:14:20 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	builtin_echo(t_command *cmd)
{
	t_list	*temp;

	if (cmd->flags && (cmd->flags->next || \
						ft_strcmp(cmd->flags->content, "-n")))
	{
		ft_putstr_fd("minishell: cd only supports '-n' flag", 1); //check if needs a new line at the end, also check if it is 1 or 2
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
