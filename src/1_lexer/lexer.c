/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanessasantos <vanessasantos@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:09:51 by vados-sa          #+#    #+#             */
/*   Updated: 2024/07/16 14:17:50 by vanessasant      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct s_token
{
	char	*type; //typedef enum struct?
	char	*value;
}	t_token;

typedef struct s_data
{
	char		**envp;
	char		*i_str;
	int			input;
	int			output;
	t_token		token;
	t_command	command;
}	t_data;

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

void	tokenize(/* t_data *data,  */char input)
{
	
}

int	lexical_analysis(/* t_data *data,  */char *input)
{
	int	i;

	if (unclosed_quotes(input) == 1)
		return(/*free_things(), */1);
	i = -1;
	/* while(input[--i])
	{
		tokenize(input[i]);
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