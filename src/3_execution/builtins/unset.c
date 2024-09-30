/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 23:20:43 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/30 13:39:38 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
			compare_len = equal_pos - data->env[i];
		else
			compare_len = ft_strlen(data->env[i]);
		if (!ft_strncmp(data->env[i], var, var_len) && var_len == compare_len)
			return (i);
		i++;
	}
	return (-1);
}

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
