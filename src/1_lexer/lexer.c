/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:09:51 by vados-sa          #+#    #+#             */
/*   Updated: 2024/07/12 12:30:49 by vados-sa         ###   ########.fr       */
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
	return (sing_quote_open || doub_quote_open);
}

int	lexical_analysis(/* t_data *data,  */char *input)
{
	int	i;

	i = 0;
	if (unclosed_quotes(input) == 1)
	{
		printf("Unclosed quote found.\n");
		return(/*free_things(), */1);
	}
	/* while(input[i])
	{
		
	} */
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