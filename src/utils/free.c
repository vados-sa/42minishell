/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:13:36 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/05 16:55:54 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_double_pointer_char(char**str)
{
	int	i;

	if (!str)
		return;
	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

void	free_double_pointer_int(int**n)
{
	int	i;

	i = 0;
	if (n)
	{
		while (n[i])
		{
			free(n[i]);
			i++;
		}
		free(n);
	}
}

void	free_substr(char **s1, char **s2, char **s3)
{
	if (*s1)
	{
		free (*s1);
		*s1 = NULL;
	}
	if (*s2)
	{
		free (*s2);
		*s2 = NULL;
	}
	if (*s3)
	{
		free (*s3);
		*s3 = NULL;
	}
}

/**
 * @brief Frees the t_data structure and all its dynamically allocated members.
 * 
 * @param data Pointer to the t_data structure.
 */
void	free_data(t_data *data)
{
	if (data->args)
		free(data->args);
	if (data->env)
		free_double_pointer_char(data->env);
	if (data->path)
		free(data->path);
	if (data->input_type)
		free(data->input_type);
	if (data->input_value)
		free(data->input_value);
	if (data->output_type)
		free(data->output_type);
	if (data->output_value)
		free(data->output_value);
	if (data->token)
		free_tokens(data->token);
	if (data->command)
		free_commands(data->command);
}
