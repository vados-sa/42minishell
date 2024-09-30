/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:09:51 by vados-sa          #+#    #+#             */
/*   Updated: 2024/09/30 11:59:12 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	tokenize(t_data *data, char *cpy_arg)
{
	int	i;
	int	j;

	i = 0;
	while (cpy_arg[i])
	{
		j = i;
		if (ft_isspace(cpy_arg[i]))
			i++;
		else if (look_for_operator(cpy_arg[i]))
			i += handle_operator(data, &cpy_arg[i]);
		else if (look_for_quotes(cpy_arg[i]))
			i += handle_quotes(data, &cpy_arg[i]);
		else
			i += handle_word(data, &cpy_arg[i]);
		if (i < j)
			return (EXIT_FAIL);
	}
	return (EXIT_SUCC);
}

int	lex(t_data *data)
{
	char	*cpy_arg;

	cpy_arg = data->args;
	if (check_input(cpy_arg))
		return (EXIT_FAIL);
	if (tokenize(data, cpy_arg))
		return (EXIT_FAIL); 
	return (EXIT_SUCC);
}
