/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 23:20:43 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/16 14:40:50 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @brief Finds the index of a variable in the environment array.
 * 
 * This function searches for the environment variable `var` in the `data->env` array.
 * It checks for an exact match of the variable name up to the '=' character.
 *
 * @param var The variable name to search for.
 * @param data The main data structure containing the environment variables array.
 * @return The index of the variable if found, or -1 if not found.
 */
static int	find_env_var_index(char *var, t_data *data)
{
	int		i;
	int		var_len;
	char	*equal_pos;
	int		compare_len;

	i = 0;
	var_len = ft_strlen(var);
	while (data->env[i])
	{
		equal_pos = ft_strchr(data->env[i], '=');
		if (equal_pos)
			compare_len = equal_pos - data->env[i]; // Length up to '='
		else
			compare_len = ft_strlen(data->env[i]); // Full length if no '='
		if (!ft_strncmp(data->env[i], var, var_len) && var_len == compare_len)
			return (i);
		i++;
	}
	return (-1);
}

/**
 * @brief Removes a variable from the environment array.
 * 
 * This function removes the environment variable `var` from the `data->env` array
 * by shifting all subsequent variables down to fill the gap. It also frees the
 * memory associated with the removed variable.
 *
 * @param var The variable to remove.
 * @param data The main data structure containing the environment variables array.
 * @return EXIT_SUCC after attempting to remove the variable.
 */
static int	remove_from_env(char *var, t_data *data)
{
	int	i;
	int	j;

	i = find_env_var_index(var, data);
	if (i != -1)
	{
		free(data->env[i]);
		j = i;
		while (data->env[j + 1])
		{
			data->env[j] = data->env[j + 1];
			j++;
		}
		data->env[j] = NULL;
	}
	return (EXIT_SUCC);
}

/**
 * @brief Builtin function to unset environment variables.
 * 
 * This function removes environment variables from the `data->env` array based on
 * the arguments passed to the `unset` command. It validates each argument before
 * attempting to remove the corresponding variable.
 *
 * @param cmd The current command structure.
 * @param data The main data structure containing the environment variables array.
 * @return EXIT_SUCC if all variables were successfully removed, EXIT_FAIL if there was an error.
 */
int	builtin_unset(t_command *cmd, t_data *data)
{
	t_list	*current_arg;

	current_arg = cmd->arguments;
	if (cmd->flags)
	{
		ft_putstr_fd("unset doesn't support options", STDERR_FILENO);
		return (EXIT_FAIL);
	}
	while (current_arg)
	{
		remove_from_env(current_arg->content, data);
		current_arg = current_arg->next;
	}
	return (EXIT_SUCC);
}
