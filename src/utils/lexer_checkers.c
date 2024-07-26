/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checkers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:24:42 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/07/26 16:25:55 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_double_operator(char *arg)
{
	if (!look_for_operator(*(arg + 1)))
		return (EXIT_SUCCESS);
	else
	{
		if ((*arg == '<' && *(arg + 1) == '<') 
			|| (*arg == '>' && *(arg + 1) == '<'))
			return (EXIT_SUCCESS);
		else
		{
			//print error message.
			return (EXIT_FAILURE);
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
			return (EXIT_FAILURE);
		i++;
	}
	if (cpy_arg[i] == '|')
		return (print_error_code(PIPE_SINTAX_ERROR, cpy_arg[i], EXIT_FAILURE));
	if (unclosed_quotes(cpy_arg))
		return (print_error_code(QUOTE_SINTAX_ERROR, cpy_arg[i], EXIT_FAILURE));
	len = ft_strlen(cpy_arg);
	while (len > 0 && ft_isspace(cpy_arg[len - 1]))
		len--;
	if (look_for_operator(cpy_arg[len -1]))
		return (print_error_code(OPER_SINTAX_ERROR, cpy_arg[len - 1], EXIT_FAILURE));
	return (EXIT_SUCCESS);
}
