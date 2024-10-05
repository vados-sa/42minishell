/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 23:20:43 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/10/05 18:21:16 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	count_quotes(char *str, int *count, char quote_type)
{
	int	i;

	i = 0;
	*count = 0;
	while (str[i])
	{
		if (str[i] == quote_type)
			(*count)++;
		i++;
	}
}

static void	copy_without_quotes(char *str, int *src_pos, int *dst_pos, \
char quote_type)
{
	while (str[*src_pos])
	{
		if (str[*src_pos] == quote_type)
		{
			(*src_pos)++;
			continue ;
		}
		str[(*dst_pos)++] = str[(*src_pos)++];
	}
}

static void	remove_even_quotes(char *str, char quote_type)
{
	int	src_pos;
	int	dst_pos;
	int	count;

	count_quotes(str, &count, quote_type);
	src_pos = 0;
	dst_pos = 0;
	if (ft_iseven(count))
		copy_without_quotes(str, &src_pos, &dst_pos, quote_type);
	else
	{
		while (str[src_pos])
			str[dst_pos++] = str[src_pos++];
	}
	str[dst_pos] = '\0';
}

int	builtin_echo(t_command *cmd)
{
	t_list	*temp;

	if (cmd->flags && (cmd->flags->next || \
						ft_strcmp(cmd->flags->content, "-n")))
	{
		ft_putstr_fd("minishell: echo only supports '-n' flag\n", 2);
		return (EXIT_FAIL);
	}
	temp = cmd->arguments;
	while (temp)
	{
		remove_even_quotes(temp->content, SINGLE_Q);
		remove_even_quotes(temp->content, DOUBLE_Q);
		ft_putstr_fd(temp->content, 1);
		if (temp->next)
			ft_putstr_fd(" ", 1);
		temp = temp->next;
	}
	if (!cmd->flags)
		ft_putstr_fd("\n", 1);
	return (EXIT_SUCC);
}
