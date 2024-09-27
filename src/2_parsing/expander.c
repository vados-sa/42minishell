/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:29:30 by vados-sa          #+#    #+#             */
/*   Updated: 2024/09/27 12:35:34 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_single_quote_state(char *str, int index)
{
	int	i;
	int	inside_double_quotes;
	int	inside_single_quotes;

	i = 0;
	inside_double_quotes = 0;
	inside_single_quotes = 0;
	while (i < index)
	{
		if (str[i] == '"' && !inside_single_quotes)
			inside_double_quotes = !inside_double_quotes;
		else if (str[i] == '\'' && !inside_double_quotes)
			inside_single_quotes = !inside_single_quotes;
		i++;
	}
	return (inside_single_quotes);
}

int	expand_var(char **str, t_data *data)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while ((*str)[i])
	{
		if ((*str)[i] == '$' && (*str)[i + 1] && (*str)[i + 1] != ' ')
		{
			if (check_single_quote_state(*str, i) == 0)
			{
				temp = concat_expanded_var(str, &i, data);
				if (!temp)
					return (EXIT_FAIL);
				free(*str);
				*str = temp;
			}
			else
				i++;
		}
		else
			i++;
	}
	return (EXIT_SUCC);
}

static int	expand_command(t_command *cmd_node, t_data *data)
{
	while (cmd_node)
	{
		if (cmd_node->type_quote != '\'')
		{
			if (expand_var(&cmd_node->command, data))
				return (EXIT_FAIL);
		}
		cmd_node = cmd_node->next;
	}
	return (EXIT_SUCC);
}

static int	expand_list_of_str(t_list *list, t_data *data)
{
	while (list)
	{
		if (list->type_quote != '\'')
		{
			if (expand_var(&list->content, data))
				return (EXIT_FAIL);
		}
		list = list->next;
	}
	return (EXIT_SUCC);
}

int	expand_tokens(t_data *data)
{
	t_command	*current_cmd_node;

	current_cmd_node = data->command;
	while (current_cmd_node)
	{
		if (expand_command(current_cmd_node, data))
			return (EXIT_FAIL);
		if (expand_list_of_str(current_cmd_node->arguments, data))
			return (EXIT_FAIL);
		if (expand_list_of_str(current_cmd_node->flags, data))
			return (EXIT_FAIL);
		current_cmd_node = current_cmd_node->next;
	}
	return (EXIT_SUCC);
}
