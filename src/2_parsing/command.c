/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:59:32 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/08/05 17:13:54 by mrabelo-         ###   ########.fr       */
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
		data->token = new;
		return ;
	}
	last->next = new;
}

int	fill_node(t_command *node, t_token *token, char *flag)
{
	if (!node)
		return (EXIT_FAILURE);
	if (flag == 'COMMAND')
	{
		node->command = ft_strdup(token->value);
		if (!node->command)
			return (EXIT_FAILURE);
		node->command_quote = token->type_quote;
	}
	else if (flag == 'FLAG')
	{
		if (add_new_list_node(&node->flags, token))
			return (EXIT_FAILURE);
	}
	else if (flag == 'ARGUMENT')
	{
		if (ft_strcmp(node->command, "export"))
		{
			if (add_new_list_node(&node->arguments, token))
				return (EXIT_FAIL);
		}
		else
			helper_export_builtin(node, token);
	}
	return (EXIT_SUCCESS);
}

int	add_new_list_node()
{
	
}

void	help_export_builtin(t_command *command, t_token *token)
{
	
}
