/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:52:26 by vados-sa          #+#    #+#             */
/*   Updated: 2024/09/10 18:03:20 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Frees a linked list of t_list nodes.
 *
 * @param list Pointer to the head of the linked list.
 */
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

/**
 * @brief Frees a linked list of t_command nodes, including arguments, flags, and final_av.
 *
 * @param commands Pointer to the head of the linked list.
 */
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
			free_double_pointer_char(temp->final_av);
		free(temp);
		temp = NULL;
	}
}

/**
 * @brief Frees a linked list of t_token nodes.
 *
 * @param tokens Pointer to the head of the linked list.
 */
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
