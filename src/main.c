/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanessasantos <vanessasantos@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:17:19 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/06/27 15:21:03 by vanessasant      ###   ########.fr       */
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
		}
		printf("%s\n", rl);
		free(rl);   
	}
}

int	main(void)
{
	// Initialization
	// Interpretation
	promt();
	// Terminate
	return (EXIT_SUCCESS);
}
