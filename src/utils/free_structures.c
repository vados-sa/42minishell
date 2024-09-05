/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:52:26 by vados-sa          #+#    #+#             */
/*   Updated: 2024/09/05 16:55:04 by vados-sa         ###   ########.fr       */
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
		if (temp->content)
			free(temp->content);
		free(temp);
	}
}

/**
 * @brief Frees a linked list of t_command nodes, including arguments, flags, and final_av.
 * 
 * @param commands Pointer to the head of the linked list.
 */
void	free_commands(t_command *commands)
{
	t_command	*temp;

	while (commands)
	{
		temp = commands;
		commands = commands->next;
		if (temp->command)
			free(temp->command);
		if (temp->arguments)
			free_list(temp->arguments);
		if (temp->flags)
			free_list(temp->flags);
		if (temp->final_av)
			free_double_pointer_char(temp->final_av);
		free(temp);
	}
}

/**
 * @brief Frees a linked list of t_token nodes.
 * 
 * @param tokens Pointer to the head of the linked list.
 */
void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		if (temp->value)
			free(temp->value);
		if (temp->type)
			free(temp->type);
		free(temp);
	}
}
