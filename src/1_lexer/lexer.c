/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanessasantos <vanessasantos@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:09:51 by vados-sa          #+#    #+#             */
/*   Updated: 2024/07/23 11:11:59 by vanessasant      ###   ########.fr       */
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
	while(input[++i])
	{
		if (input[i] == '\'' && !doub_quote_open)
			sing_quote_open = !sing_quote_open;
		else if (input[i] == '"' && !sing_quote_open)
			doub_quote_open = !doub_quote_open;
	}
	if (sing_quote_open || doub_quote_open)
		printf("Unclosed quote found.\n");
	return (sing_quote_open || doub_quote_open);
}

int	skip_white_spaces(char *input, int i)
{
	while (input[i] == 32 || (input[i] >= 9 && input[i] <=13))
		i++;
	return(i);
}

int	check_for_operator(char c)
{
	if (c == ">" || c == "<" || c == "|")
		return (1);
	return (0);
}

int	tokenize(/* t_data *data,  */char *input)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while(input[i])
	{
		i += skip_white_spaces(input, i);
		j = 0;
		if (check_for_operator(input[i]) == 1)
			handle_operator();
		else
			read_word();
	}
	return (0);
}

int	lexical_analysis(/* t_data *data,  */char *input)
{
	if (unclosed_quotes(input) == 1)
		return(/*free_things(), */1);
	tokenize(input);
	return (0);
}

int	main(void)
{
	char	*rl;
	/* t_data	*data; */

	rl = "echo \"Hi\"I'm \"Vanessa\"";
	printf("%s\n", rl);
	lexical_analysis(/* data,  */rl);
	return (0);
}