/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:17:19 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/07/02 14:28:26 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    promt(void)
{
	char    *rl;

	while (1)
	{
		rl = readline("minishell> ");
		if (rl == NULL)
		{
			printf("\n");
			exit (EXIT_FAILURE);
		}
		if (rl[0] != '\0')
		{
			add_history(rl);
			//Lexing and Parsing
			//Exec
		}
		printf("%s\n", rl);
		free(rl);
		//cleanup   
	}
}

int	main(int ac, char *av[], char **env)
{
	if (ac =! 1)
	{
		//error
		return (EXIT_FAILURE);
	}
	av = NULL;
	// Initialize data
		// exit program if error -> check if mem management is necessary
	// Interpretation
	promt(); //cleanup is at the end of the loop
	// Terminate
	return (EXIT_SUCCESS);
}
