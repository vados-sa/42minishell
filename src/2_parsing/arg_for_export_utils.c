/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_for_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:44:51 by vados-sa          #+#    #+#             */
/*   Updated: 2024/09/30 13:09:11 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_first_quote(char *str, char *quote)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			*quote = str[i];
			return (i + 1);
		}
		i++;
	}
	return (-1);
}

static int	is_quote_closed(char *str, char quote, int start)
{
	int	i;

	i = start;
	while (str[i])
	{
		if (str[i] == quote)
			return (1);
		i++;
	}
	return (0);
}

void	closed_quote(char *str, int *add_new_node)
{
	char	quote;
	int		start;

	quote = '\0';
	if (!str)
	{
		ft_putstr_fd("closed_quote: string is NULL\n", 2);
		return ;
	}
	start = find_first_quote(str, &quote);
	if (start == -1)
	{
		*add_new_node = 1;
		return ;
	}
	*add_new_node = is_quote_closed(str, quote, start);
}
