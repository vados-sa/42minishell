/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:52:26 by vados-sa          #+#    #+#             */
/*   Updated: 2024/10/01 17:04:41 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_list(t_list *list)
{
	t_list	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		temp->next = NULL;
		if (temp->content)
		{
			free(temp->content);
			temp->content = NULL;
		}
		free(temp);
		temp = NULL;
	}
}

void	free_commands(t_data *data)
{
	t_command	*temp;

	while (data->command)
	{
		temp = data->command;
		data->command = data->command->next;
		temp->next = NULL;
		if (temp->command)
		{
			free(temp->command);
			temp->command = NULL;
		}
		if (temp->arguments)
			free_list(temp->arguments);
		if (temp->flags)
			free_list(temp->flags);
		if (temp->final_av)
			free_double_pointer_char(&temp->final_av);
		free(temp);
		temp = NULL;
	}
}

void	free_tokens(t_data *data)
{
	t_token	*temp;

	while (data->token)
	{
		temp = data->token;
		data->token = data->token->next;
		temp->next = NULL;
		if (temp->value)
		{
			free(temp->value);
			temp->value = NULL;
		}
		free(temp);
		temp = NULL;
	}
}

void	free_env_and_path(t_data *data)
{
	if (!data)
		return ;
	if (data->env)
		free_double_pointer_char(&data->env);
	if (data->path)
	{
		free(data->path);
		data->path = NULL;
	}
}

