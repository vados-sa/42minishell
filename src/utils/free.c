/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:13:36 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/19 14:10:25 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_double_pointer_char(char**str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		if (str[i])  // Extra safeguard to ensure the pointer is valid
		{
			free(str[i]);
			str[i] = NULL;  // Setting to NULL to avoid double free
		}
		i++;
	}
	free(str);
	str = NULL;
}

void	free_double_pointer_int(int**n, int qt_cmd)
{
	int	i;

	if (!n)
		return ;
	i = 0;
	while (i < qt_cmd - 1)
	{
		if (n[i])
		{
			free(n[i]);
			n[i] = NULL;
		}
		i++;
	}
	free(n);
	n = NULL;
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
	if (!data)
		return ;
	if (data->args)
	{
		free(data->args);
		data->args = NULL;
	}
	data->input_type = STDIN;
	data->input_fd = STDIN_FILENO;
	if (data->input_value)
	{
		free(data->input_value);
		data->input_value = NULL;
	}
	data->output_type = STDOUT;
	data->output_fd = STDOUT_FILENO;
	if (data->output_value)
	{
		free(data->output_value);
		data->output_value = NULL;
	}
	if (data->token)
		free_tokens(data);
	if (data->command)
		free_commands(data);
}

void	free_env_and_path(t_data *data)
{
	if (!data)
		return ;
	if (data->env)
		free_double_pointer_char(data->env);
	if (data->path)
	{
		free(data->path);
		data->path = NULL;
	}
}
