/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:17:19 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/06 14:27:06 by mrabelo-         ###   ########.fr       */
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
			minishell_exit(data, EXIT_SUCC);
		signals_non_interactive_handler();
		if (data->args[0])
			add_history(data->args);
		if (lex(data) || parse(data) || exec(data))
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
		minishell_exit(&data, EXIT_FAIL);
	minishell_loop(&data);
	return (EXIT_SUCC);
}
