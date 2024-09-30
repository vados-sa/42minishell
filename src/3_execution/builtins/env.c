/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 23:20:43 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/30 13:38:15 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// CHECK IF QUOTES ARE BEING PRINTED -> IT SHOULDN'T !

static int	has_an_equal_sign(char *variable)
{
	int	i;

	i = 0;
	while (variable[i])
	{
		if (variable[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	builtin_env(t_command *cmd, t_data *data)
{
	int	i;

	i = 0;
	if (cmd->flags || cmd->arguments)
	{
		ft_putstr_fd("minishell: env doesn't support options or arguments\n", \
			STDERR_FILENO);
		return (EXIT_FAIL);
	}
	while (data->env[i])
	{
		if (has_an_equal_sign(data->env[i]))
			printf("%s\n", data->env[i]);
		i++;
	}
	return (EXIT_SUCC);
}
