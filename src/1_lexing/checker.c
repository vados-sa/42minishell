/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:24:42 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/10/08 19:05:54 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_double_operator(char *arg)
{
	if (!look_for_operator(*(arg + 1)))
		return (EXIT_SUCC);
	else
	{
		if ((*arg == '<' && *(arg + 1) == '<')
			|| (*arg == '>' && *(arg + 1) == '>'))
			return (EXIT_SUCC);
		else
		{
			return (print_error_code(OTHER_STX_ERROR, *(arg + 1), EXIT_FAIL));
		}
	}
}

int	check_input(char *cpy_arg)
{
	int	i;
	int	len;

	i = 0;
	while (ft_isspace(cpy_arg[i]))
	{
		if (!cpy_arg[i + 1])
			return (EXIT_FAIL);
		i++;
	}
	if (cpy_arg[i] == '|')
		return (print_error_code(PIPE_STX_ERROR, cpy_arg[i], EXIT_FAIL));
	if (unclosed_quotes(cpy_arg))
		return (print_error_code(QUOTE_STX_ERROR, cpy_arg[i], EXIT_FAIL));
	len = ft_strlen(cpy_arg);
	while (len > 0 && ft_isspace(cpy_arg[len - 1]))
		len--;
	if (len == 0)
		return (EXIT_FAIL);
	if (look_for_operator(cpy_arg[len -1]))
		return (print_error_code(OTHER_STX_ERROR, cpy_arg[len -1], EXIT_FAIL));
	return (EXIT_SUCC);
}

int	unclosed_quotes(char *input)
{
	int	i;
	int	sing_quote_open;
	int	doub_quote_open;

	i = -1;
	sing_quote_open = 0;
	doub_quote_open = 0;
	while (input[++i])
	{
		if (input[i] == '\'' && !doub_quote_open)
			sing_quote_open = !sing_quote_open;
		else if (input[i] == '\"' && !sing_quote_open)
			doub_quote_open = !doub_quote_open;
	}
	return (sing_quote_open || doub_quote_open);
}

int	outer_quote(char *arg)
{
	int	i;
	int	pos;
	int	pos_count;

	i = 1;
	pos = 1;
	pos_count = 1;
	while (arg[i])
	{
		if (arg[i] == arg[0])
		{
			pos = i;
			pos_count++;
		}
		if (ft_iseven(pos_count) && (look_for_operator(arg[i]) || !arg[i + 1]))
		{
			return (pos);
		}
		i++;
	}
	return (i);
}
