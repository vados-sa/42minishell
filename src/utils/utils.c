/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:40:41 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/05 15:06:50 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	look_for_quotes(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	look_for_operator(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

char	*get_env_value(char *env_var, t_data *data)
{
	int		i;
	char	*value;
	int		var_len;

	i = 0;
	value = NULL;
	var_len = ft_strlen(env_var);
	while (data->env[i])
	{
		if (!ft_strncmp(env_var, data->env[i], var_len) && 
			data->env[i][var_len] == '=')
		{
			value = ft_strdup(data->env[i] + var_len + 1);
			if (!value)
				return (NULL);
			return (value);
		}
		i++;
	}
	return (NULL);
}

int	add_value_to_env(char *env_var, char *value, t_data *data)
{
	int		i;
	int		var_len;
	char	*new_entry;

	i = 0;
	var_len = ft_strlen(env_var);
	new_entry = NULL;
	while (data->env[i])
	{
		if (!ft_strncmp(env_var, data->env[i], var_len) && 
			data->env[i][var_len] == '=')
		{
			new_entry = malloc(var_len + ft_strlen(value) + 1);
			if (!new_entry)
				exit(EXIT_FAILURE);
			ft_strcpy(new_entry, env_var);
			ft_strcpy(new_entry + var_len, value);
			free(data->env[i]);
			data->env[i] = new_entry;
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (1); // enviroment variable not found
}

int	check_invalid_identifiers(char *arg, char *command)
{
	int	i;

	i = 0;
	if (!arg[0] || (!ft_isalpha(arg[0]) && arg[0] != '_'))
	{
		printf("minishell: %s: `%s': not a valid identifier\n", command, arg);
		return (EXIT_FAILURE);
	}
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '=' && !ft_strcmp(command, "export"))
			break ;
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			printf("minishell: %s: `%s': not a valid identifier\n", \
					command, arg);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
