/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:09:51 by vados-sa          #+#    #+#             */
/*   Updated: 2024/07/26 16:26:00 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Checks for any unclosed quotes. I none are found, it returns 0.*/
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

int	look_for_quotes(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	look_for_operator(char c)
{
	if (c == ">" || c == "<" || c == "|")
		return (1);
	return (0);
}


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
			i += handle_operator();
		else if (look_for_quotes(cpy_arg[i]))
			i += handle_quotes();
		else
			i += handle_word();
		if (i < j)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	lex(t_data *data)
{
	char	*cpy_arg;
	int		i;

	i = 0;
	cpy_arg = data->args;
	if (check_input(cpy_arg))
		return (EXIT_FAILURE);
	if (tokenize(data, cpy_arg))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/* int	main(void)
{
	char	*rl;
	/* t_data	*data; 

	rl = "echo \"Hi\"I'm \"Vanessa\"";
	printf("%s\n", rl);
	lexical_analysis(/* data,  rl);
	return (0);
}
*/