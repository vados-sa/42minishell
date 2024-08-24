/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arg_for_export.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:37:06 by vados-sa          #+#    #+#             */
/*   Updated: 2024/08/24 19:48:02 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

 // for test 09, checar se a string tem typo quote pelo token structure
int	open_quotes(t_command *cmd_node)
{
	t_list	*lst_arg;
	int		quote_count;
	int		i;
	char	quote;

	quote_count = 0;
	i = 0;
	quote = '\0';
	lst_arg = ft_lst_last(cmd_node->arguments);
	while (lst_arg->content[i] != '\'' && lst_arg->content[i] != '\"')
	{
		if (lst_arg->content[i + 1] == '\'' || lst_arg->content[i + 1] == '\"')
			quote = lst_arg->content[i + 1];
		i++;
	}
	if (quote != '\0')
	{
		while (lst_arg->content[i])
		{
			if (lst_arg->content[i] == quote)
				quote_count++;
			i++;
		}
	}
	return (quote_count % 2 != 0);
}

 // might not handle all cases #crying
void	closed_quote(char *str, int *add_new_node)
{
	int		i;
	char	quote;
	int		quote_qnt;

	i = 0;
	quote = '\0';
	quote_qnt = 0;
	if (!str)
	{
		printf("closed_quote: string is NULL\n");
		return ;
	}
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			quote_qnt++;
			break ;
		}
		i++;
	}
	if (quote_qnt == 0)
	{
		*add_new_node = 1;
		return ;
	}
	i++;
	while (str[i])
	{
		if (str[i] == quote)
			*add_new_node = 1;
		i++;
	}
	*add_new_node = 0;
}

char	*get_equal_sign_pos(t_command *cmd_node)
{
	t_list	*ptr;
	char	*equal_pos;

	ptr = cmd_node->arguments;
	while (ptr->next)
		ptr = ptr->next;
	if (!ptr || !ptr->content)
	{
		printf("Pointer or content is NULL\n");
		return (NULL);
	}
	equal_pos = ft_strchr(ptr->content, '=');
	if (!equal_pos)
		return (NULL);
	return (equal_pos);
}

int	concat_arguments(t_command *cmd_node, t_token *token, int *add_new_node)
{
	t_list	*current_arg;
	char	*temp;

	current_arg = cmd_node->arguments;
	while (current_arg->next)
		current_arg = current_arg->next;
	temp = ft_concat(current_arg->content, " ", token->value);
	if (!temp)
		return (EXIT_FAILURE);
	free (current_arg->content);
	current_arg->content = temp;
	closed_quote(temp, add_new_node);
	return (EXIT_SUCCESS);
}

int	handle_export_builtin_arg(t_command *cmd_node, t_token *token)
{
	char		*equal_pos;
	static int	add_new_node;

	if (!cmd_node->arguments || add_new_node == 1)
	{
		add_new_list_node(&cmd_node->arguments, token);
		equal_pos = get_equal_sign_pos(cmd_node);
		if (equal_pos && equal_pos[1])
			closed_quote((equal_pos + 1), &add_new_node);
	}
	else
	{
		equal_pos = get_equal_sign_pos(cmd_node);
		if (equal_pos && *(equal_pos + 1) && open_quotes(cmd_node))
		{
			if (concat_arguments(cmd_node, token, &add_new_node))
				return (EXIT_FAILURE);
		}
		else
		{
			add_new_list_node(&cmd_node->arguments, token);
			add_new_node = 0;
		}
	}
	return (EXIT_SUCCESS);
}

// CHECK FOR INVALID IDENTIFIERS
// this will probably go into export.
/* if (!ft_isalpha(token->value[i]) && token->value[i] != '_') // invalid indetifier error
	{
		printf("bash: export: `%s': not a valid identifier\n", token->value);
		return (EXIT_FAILURE);
	}
	while (token->value[i] || token->value[i] != '=') // FIND '=' OR 'space'
	{
		if (!ft_isalnum(token->value[i]) && token->value[i] != '_')
			return (EXIT_FAILURE); // invalid identifier error
		i++;
	} */