/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 23:20:43 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/30 13:38:57 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//CHECK IF QUOTES ARE BEING PRINTED -> IT SHOULD !

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

static void	copy_env_vars(char **new_env, char **old_env, int env_size)
{
	int	i;

	i = 0;
	while (i < env_size)
	{
		new_env[i] = old_env[i];
		i++;
	}
}

static int	add_new_var(t_data *data, char *var, int i)
{
	char	**new_env;
	int		env_size;

	env_size = 0;
	while (data->env[env_size])
		env_size++;
	new_env = malloc(sizeof(char *) * (env_size + 2));
	if (!new_env)
	{
		perror("failed to allocate new environment array");
		return (EXIT_FAIL);
	}
	copy_env_vars(new_env, data->env, env_size);
	//free_old_env(data->env, env_size);
	free(data->env);
	data->env = new_env;
	data->env[i] = ft_strdup(var);
	if (!data->env[i])
	{
		perror("failed to create new environment variable.");
		//free(new_env);
		return (EXIT_FAIL);
	}
	data->env[i + 1] = NULL;
	return (EXIT_SUCC);
}

int	update_env_array(char *var, t_data *data)
{
	int		var_len;
	int		i;
	char	*equal_pos;

	var_len = 0;
	while (var[var_len] && var[var_len] != '=')
		var_len++;
	i = 0;
	while (data->env[i])
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

static int	loop_args(t_list *current_arg, t_data *data)
{
	int	es_flag;

	es_flag = 0;
	while (current_arg)
	{
		if (check_invalid_identifiers(current_arg->content))
		{
			es_flag = 1;
			current_arg = current_arg->next;
			continue ;
		}
		if (update_env_array(current_arg->content, data))
			return (EXIT_FAIL);
		current_arg = current_arg->next;
	}
	if (es_flag)
		return (EXIT_FAIL);
	return (EXIT_SUCC);
}

int	builtin_export(t_command *cmd, t_data *data)
{
	if (cmd->flags)
	{
		ft_putstr_fd("export doesn't support options", STDERR_FILENO);
		return (EXIT_FAIL);
	}
	if (!cmd->arguments)
	{
		print_env_var(data);
		return (EXIT_SUCC);
	}
	return (loop_args(cmd->arguments, data));
}
