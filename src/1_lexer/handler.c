/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:36:22 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/07/26 10:17:47 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	look_for_operator(char c) // tirar depois que for testado
{
	if (c == ">" || c == "<" || c == "|")
		return (1);
	return (0);
}

int	check_dub_redirect(char *arg)
{
	if (!look_for_operator(*(arg + 1)))
		return (EXIT_SUCCESS);
	else
	{
		if ((*arg == '<' && *(arg + 1) == '<') 
			|| (*arg == '>' && *(arg + 1) == '<'))
			return(EXIT_SUCCESS);
		else
		{
			//print error message.
			return(EXIT_FAILURE);
		}
	}
}

int	handle_operator(t_data *data, char *arg, int pos)  // needs t_data to be able to save the token.
{
	int 	i;

	i = 0;
	if (check_dub_redirect(arg[pos]))
		return(-1);
	if ((arg[pos] == '<' || arg[pos] == '>'))
		i += save_redirection();
	if (arg[pos] == '|')
	{
		i++;
		//save pipe token
	}
	//check if there is information after the operator
	//check if it is only "<" and ">" OR "<<" and ">>"
	//handle redirection
	//handle pipe
	//create token
	//in case of sucess return how many positions to move in the string
	return (i);
}

int	handle_quotes(t_data *data, char *arg, int pos) // needs t_data to be able to save the token.
{
	char *end_quote;
	int	i;

	i = pos;
	end_quote = arg;
	while (end_quote[i + 1] != arg[pos])
		i++;
	if (arg[pos] == '\"')
		;// save token DQ
	else
		;// save token SQ
	//in case of error return -1;
	return (i - pos);
}

int	handle_word(t_data *data, char *arg, int pos)  // needs t_data to be able to save the token.
{
	int	i;

	i = pos;
	while(arg[i] || !ft_isspace(arg[i]) || !look_for_operator(arg[i]))
		i++;
	// save string/word token from pos to i
	//in case of error return -1;
	return (i - pos);
}