/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:59:32 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/08/07 11:34:18 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*create_command_node(t_data *data)
{
	t_command	*new_command;

	if (!data->command)
	{
		data->command = ft_calloc(1, sizeof(t_command));
		if (!data->command)
		{
			perror("malloc new command node");
			return (NULL);
		}
		return (data->command);
	}
	else
	{
		new_command = ft_calloc(1, sizeof(t_command));
		if (!new_command)
		{
			perror("malloc new command node");
			return (NULL);
		}
		create_command_list(data, new_command);
		return (new_command);
	}
}

void	create_command_list(t_data *data, t_command *new)
{
	t_command	*last;

	last = ft_lst_last_command(data->command);
	if (!last)
	{
		data->command = new;
		return ;
	}
	last->next = new;
}

int	fill_node(t_command *node, t_token *token, char *flag)
{
	if (!node)
		return (EXIT_FAILURE);
	if (ft_strcmp(flag, "COMMAND") == 0)
	{
		node->command = ft_strdup(token->value);
		if (!node->command)
			return (EXIT_FAILURE);
		node->type_quote = token->type_quote;
	}
	else if (ft_strcmp(flag, "FLAG") == 0)
	{
		if (add_new_list_node(&node->flags, token))
			return (EXIT_FAILURE);
	}
	else if (ft_strcmp(flag, "ARGUMENT") == 0)
	{
		if (ft_strcmp(node->command, "export") == 0)
			;//helper_export_builtin
		else
		{
			if (add_new_list_node(&node->arguments, token))
				return (EXIT_FAIL);
		}
	}
	return (EXIT_SUCCESS);
}

int	add_new_list_node(t_list **lst, t_token *token)
{
	t_list	*new;

	new = ft_calloc(1, sizeof(t_list));
	if (!new)
		return (perror_return_error("malloc new list node"));
	new->content = ft_strdup(token->value);
	if (!new->content)
		return (perror_return_error("ft_strdup new list node"));
	new->type_quote = token->type_quote;
	if (!*lst)
		*lst = new;
	else
		ft_lstadd_back(lst, new);
	return (EXIT_SUCC);
}

/* void	help_export_builtin(t_command *command, t_token *token)
{
	
} */
