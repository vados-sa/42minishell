/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malu <malu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:17:19 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/27 14:03:12 by malu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	minishell_loop(t_data *data)
{
	while (1)
	{
		signals_interactive_handler();
		data->args = readline("minishell$ ");
		if (!data->args)
			minishell_exit(data, EXIT_SUCC, 0);
		signals_non_interactive_handler();
		if (data->args[0])
			add_history(data->args);
		if ((lex(data) && !data->args) || parse(data))
		{
			free_data(data);
			data->exit_status = 1;
			continue ;
		}
		if (exec(data))
		{
			free_data(data);
			continue ;
		}
		free_data(data);
	}
}

int	main(int ac, char *av[], char **env)
{
	t_data	data;

	if ((ac != 1))
	{
		perror("no arguments");
		return (EXIT_FAIL);
	}
	(void)av;
	ft_memset(&data, 0, sizeof(data));
	if (init_data(&data, env))
		minishell_exit(&data, EXIT_FAIL, 0);
	minishell_loop(&data);
	return (EXIT_SUCC);
}
