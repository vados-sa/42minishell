/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:17:19 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/07/23 14:46:41 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    minishell_loop(t_data *data, char **env)
{
	init_data(data, env);
	while (1)
	{
		data->args = readline("minishell$ ");
		if (!data->args) // check: rl being NULL means Ctrl-D was pressed, signaling an end-of-file (EOF)
		{
			printf("\n");
			exit (EXIT_FAILURE);
		}
		if (data->args[0]) //check the comparison
			add_history(data->args);
		if (lex(data) || parse(data) || execute(data)) //check if needs to be lex(data) or !lex(data)
		{
			//free_memory
			continue ;
		}
		//free_memory
	}
}

int	main(int ac, char *av[], char **env)
{
	t_data	data;

	if ((ac != 1))
	{
		printf("No arguments allowed!\n");
		return (EXIT_FAILURE);
	}
	(void)av;
	setup_signal_handlers(); //look interactive and non interactive
	ft_memset(&data, 0, sizeof(data));
	minishell_loop(&data, env);
	// init_env(data, env);
		// exit program if error -> check if mem management is necessary
	return (EXIT_SUCCESS);
}
