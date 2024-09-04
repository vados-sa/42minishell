/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 23:20:43 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/04 15:50:41 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// CHECK IF QUOTES ARE BEING PRINTED -> IT SHOULDN'T !

/**
 * @brief Checks if the given variable has an equal sign, indicating it is 
 * a valid environment variable for `env`.
 * 
 * @param variable The environment variable string (e.g., "VAR=value" or "VAR=").
 * @return 1 if the variable has an equal sign, 0 otherwise.
 */

static int	has_an_equal_sign(char *variable)
{
	int	i;

	i = 0;
	while(variable[i])
	{
		if (variable[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Builtin function to display environment variables.
 * 
 * The env command outputs each environment variable that has a value.
 * If the command has any arguments or flags, it outputs an error message.
 * 
 * @param cmd The current command node.
 * @param data The main data structure containing environment variables.
 * @return EXIT_SUCC on success, EXIT_FAIL on failure.
 */
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
