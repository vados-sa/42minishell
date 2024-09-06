/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 23:20:43 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/06 13:19:53 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//CHECK IF QUOTES ARE BEING PRINTED -> IT SHOULD !

/**
 * @brief Prints all environment variables in a format suitable for 'export' command output.
 *
 * This function iterates through the environment variables stored in the `data->env`
 * array and prints each one prefixed with "declare -x ", which is the format used by the
 * 'export' command when it is invoked without any arguments.
 *
 * @param data The main data structure containing the environment variables array.
 */
static void	print_env_var(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		printf("declare -x %s\n", data->env[i]);
		i++;	
	}
}

/**
 * @brief Adds a new environment variable to the environment array.
 *
 * This function creates a new environment variable entry in the `data->env` array.
 * It duplicates the provided `var` string and assigns it to the next available slot
 * in the array. If the duplication fails, an error is printed.
 *
 * @param data The main data structure containing the environment variables array.
 * @param var The variable to be added to the environment.
 * @param i The index at which to add the new variable in the `data->env` array.
 * @return EXIT_SUCC if the variable was added successfully, EXIT_FAIL otherwise.
 */
static int	add_new_var(t_data *data, char* var, int i)
{

	data->env[i] = ft_strdup(var);
	if (data->env[i])
	{
		perror("failed to create new enviroment variable.");
		return (EXIT_FAIL);
	}
	data->env[i + 1] = NULL;
	return (EXIT_SUCC);
}

/**
 * @brief Updates an existing environment variable or adds a new one if it doesn't exist.
 *
 * This function searches for an existing environment variable in the `data->env` array
 * that matches the name of the provided `var`. If found, it updates the variable's value.
 * If not found, it calls `add_new_var` to add the new variable to the environment.
 *
 * @param var The variable to be updated or added.
 * @param data The main data structure containing the environment variables array.
 * @return EXIT_SUCC if the variable was updated or added successfully, EXIT_FAIL otherwise.
 */
static int	update_env_array(char *var, t_data *data)
{
	int		var_len;
	int		i;
	char	*equal_pos;

	var_len = 0;
	while (var[var_len] && var[var_len] != '=')
		var_len++;
	i = 0;
	while(data->env[i])
	{
		equal_pos = ft_strchr(data->env[i], '=');
		if (equal_pos && !ft_strncmp(data->env[i], var, var_len) &&
			 data->env[i][var_len] == '=')
		{
			free(data->env[i]);
			data->env[i] = ft_strdup(var);
			if (!data->env[i])
				return (EXIT_FAIL);
			return (EXIT_SUCC);
		}
		i++;
	}
	add_new_var(data, var, i);
	return (EXIT_SUCC);
}

/**
 * @brief Handles the 'export' builtin command, managing environment variables.
 *
 * This function implements the 'export' builtin command. It checks if any flags
 * are provided (which are not supported), prints all environment variables if
 * no arguments are given, or updates/adds environment variables based on the
 * provided arguments.
 *
 * @param cmd The command structure containing arguments and flags for 'export'.
 * @param data The main data structure containing the environment variables array.
 * @return EXIT_SUCC if the command executed successfully, EXIT_FAIL otherwise.
 */
int	builtin_export(t_command *cmd, t_data *data)
{
	t_list	*current_arg;

	current_arg = cmd->arguments;
	if (cmd->flags)
	{
		ft_putstr_fd("export doesn't support options", STDERR_FILENO);
		return (EXIT_FAIL);
	}
	if (!current_arg)
	{
		print_env_var(data);
		return (EXIT_SUCC);
	}
	while (current_arg)
	{
		if (check_invalid_identifiers(current_arg->content, "export"))
		{
			current_arg = current_arg->next;
			continue ;
		}
		// check later if it is a shell variable and, if so, add it to the array
		if (update_env_array(current_arg->content, data))
			return (EXIT_FAIL);
		current_arg = current_arg->next;
	}
	return (EXIT_SUCC);
}
