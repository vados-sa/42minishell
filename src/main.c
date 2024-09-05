/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:17:19 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/05 11:05:02 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	minishell_loop(t_data *data, char **env)
{
	while (1)
	{
		signals_interactive_handler();
		data->args = readline("minishell$ ");
		if (!data->args) // check: rl being NULL means Ctrl-D was pressed, signaling an end-of-file (EOF)
		{ // call a fucniton to exit minishell with a SUCCESS STATUS
			printf("\n");
			exit (EXIT_FAIL); //here is supposed to be minishell_exit too
		}
		signals_non_interactive_handler();
		if (data->args[0])
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
		return (EXIT_FAIL);
	}
	(void)av;
	ft_memset(&data, 0, sizeof(data));
	if (init_data(&data, env))
		minishell_exit(&data, EXIT_FAIL);
	minishell_loop(&data, env);
	return (EXIT_SUCC);
}
