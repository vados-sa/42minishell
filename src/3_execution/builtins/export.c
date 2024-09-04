/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 23:20:43 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/04 17:31:15 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//CHECK IF QUOTES ARE BEING PRINTED -> IT SHOULD !

static int	check_invalid_identifiers(char *arg)
{
	int	i;

	i = 0;
	if (!arg[0] || (!ft_isalpha(arg[0]) && arg[0] != '_'))
	{
		printf("bash: export: `%s': not a valid identifier\n", arg);
		return (EXIT_FAILURE);
	}
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

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

static int	add_new_var(t_data *data, char* var, int i)
{

	data->env[i] = ft_strdup(var);
	if (data->env[i])
	{
		perror("failed to create new enviroment variable.");
		return (EXIT_FAILURE);
	}
	data->env[i + 1] = NULL;
	return (EXIT_SUCCESS);
}

static int	update_env_array(char *var, t_data *data)
{
	int		var_len;
	int		i;
	char	*equal_pos;

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
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	add_new_var(data, var, i);
	return (EXIT_SUCCESS);
}

int	builtin_export(t_command *cmd, t_data *data)
{
	t_list	*current_arg;

	current_arg = cmd->arguments;
	if (cmd->flags)
	{
		ft_putstr_fd("export doesn't support options", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!current_arg)
	{
		print_env_var(data);
		return (EXIT_SUCCESS);
	}
	while (current_arg)
	{
		if (check_invalid_identifiers(current_arg->content))
			return(EXIT_FAILURE);
		// check later if it is a shell variable and, if so, add it to the array
		if (update_env_array(current_arg->content, data))
			return (EXIT_FAILURE);
		current_arg = current_arg->next;
	}
	return (EXIT_SUCCESS);
}
