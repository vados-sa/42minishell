/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:09:51 by vados-sa          #+#    #+#             */
/*   Updated: 2024/07/23 17:28:16 by mrabelo-         ###   ########.fr       */
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
		else if (input[i] == '"' && !sing_quote_open)
			doub_quote_open = !doub_quote_open;
	}
	return (sing_quote_open || doub_quote_open);
}

/* int	skip_white_spaces(char *input, int i)
{
	while (input[i] == 32 || (input[i] >= 9 && input[i] <=13))
		i++;
	return(i);
} */

int	check_for_operator(char c)
{
	if (c == ">" || c == "<" || c == "|")
		return (1);
	return (0);
}

int	tokenize(char *cpy_arg)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while(cpy_arg[i])
	{
		i += skip_white_spaces(cpy_arg, i); //check
		j = 0;
		if (check_for_operator(cpy_arg[i]) == 1)
			handle_operator();
		else
			read_word();
	}
	return (0);
}

int	check_input(char *cpy_arg)
{
	int	i;

	i = 0;
	while (ft_isspace(cpy_arg[i]))
	{
		if (!cpy_arg[i + 1])
			return (EXIT_FAILURE);
		i++;
	}
	if (cpy_arg[i] == '|')
		return (/*CREATE FUNCTION TO PRINT ERROR AND RETURN ERROR*/);
	if (unclosed_quotes(cpy_arg))
		return (/*CREATE FUNCTION TO PRINT ERROR AND RETURN ERROR*/);
}


int	lex(t_data *data)
{
	char	*cpy_arg;
	int		i;

	i = 0;
	cpy_arg = data->args;
	if (check_input(cpy_arg))
		return (EXIT_FAILURE);
	tokenize(cpy_arg);
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