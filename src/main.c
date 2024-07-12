/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanessasantos <vanessasantos@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:17:19 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/07/03 17:04:34 by vanessasant      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    minishell_loop(void) // t_data *data
{
	char    *rl;

	while (1)
	{
		rl = readline("minishell> ");
		if (rl == NULL) // rl being NULL means Ctrl-D was pressed, signaling an end-of-file (EOF)
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

int	main(int ac, char *av[]/* , char **env */)
{
	//t_data	*data;

	if ((ac != 1))
	{
		printf("No arguments allowed!\n");
		return (EXIT_FAILURE);
	}
	(void)av;
	setup_signal_handlers();
	// init_env(data, env);
		// exit program if error -> check if mem management is necessary
	minishell_loop();
	return (EXIT_SUCCESS);
}
