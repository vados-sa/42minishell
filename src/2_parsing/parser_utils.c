/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:23:36 by vados-sa          #+#    #+#             */
/*   Updated: 2024/09/30 13:13:06 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_var_len(char *str)
{
	int	i;
	int	len;

	i = 1;
	len = 0;
	if (str[1] == '{')
		i++;
	if (str[i] == '?')
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_') && str[i] != '}')
	{
		len++;
		i++;
	}
	return (len);
}

char	*get_exp_env(char *str, int len, char **env_arg)
{
	if (!env_arg)
	{
		printf("Environment variable array is NULL\n");
		return ("");
	}
	while (*env_arg)
	{
		if (!ft_strncmp(str + 1, *env_arg, len) && (*env_arg)[len] == '=')
			return (*env_arg + len + 1);
		env_arg++;
	}
	return ("");
}

void	remove_possible_quotes(char *str)
{
	int	src_pos;
	int	dst_pos;

	src_pos = 0;
	dst_pos = 0;
	while (str[src_pos])
	{
		if (str[src_pos] != SINGLE_Q && str[src_pos] != DOUBLE_Q)
		{
			str[dst_pos] = str[src_pos];
			dst_pos++;
		}
		src_pos++;
	}
	str[dst_pos] = '\0';
}

long	get_nbr_of_elements(t_command *cmd_node)
{
	long		count;
	t_list		*args;
	t_list		*flags;

	count = 1;
	args = cmd_node->arguments;
	flags = cmd_node->flags;
	while (cmd_node)
	{
		while (args)
		{
			count++;
			args = args->next;
		}
		while (flags)
		{
			count++;
			flags = flags->next;
		}
		cmd_node = cmd_node->next;
	}
	return (count);
}
