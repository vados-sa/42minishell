/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:39:34 by vados-sa          #+#    #+#             */
/*   Updated: 2024/10/08 19:02:06 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	refresh_line(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

static void	display_new_line(int sig)
{
	if (sig == SIGQUIT)
		write(STDERR_FILENO, "Quit (core dumped)\n", 19);
	if (sig == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
}

void	signals_interactive_handler(void)
{
	signal(SIGINT, refresh_line);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_non_interactive_handler(void)
{
	signal(SIGINT, display_new_line);
	signal(SIGQUIT, display_new_line);
}
