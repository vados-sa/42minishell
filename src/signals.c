/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:39:34 by vados-sa          #+#    #+#             */
/*   Updated: 2024/09/17 16:48:52 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Signal handler for interactive mode. Clears the current input line
 * and redisplays the prompt when SIGINT (Ctrl-C) is received.
 *
 * @param sig The received signal value (unused in this function)
 */
static void	refresh_line(int sig)
{
	(void)sig; // to avoid unused variable warning
	rl_replace_line("", 0); // Clear the current input line
	rl_on_new_line(); // Move the cursor to a new line
	write(STDOUT_FILENO, "\n", 1);
    rl_redisplay(); // Redisplay the prompt
}

/**
 * @brief Signal handler for non-interactive mode. Displays a new line when a
 * signal is received and prints a message if SIGQUIT (Ctrl-\) is received.
 *
 * @param sig The received signal value
 */

static void	display_new_line(int sig)
{
	if (sig == SIGQUIT)
		write(STDERR_FILENO, "Quit (core dumped)\n", 19); // Apparently needs to be ignored
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
}

/**
 * @brief Sets signal handlers for interactive mode. SIGINT (Ctrl-C) is set to
 * clear the line and redisplay the prompt. SIGQUIT (Ctrl-\) is ignored.
 */
void	signals_interactive_handler(void)
{
	signal(SIGINT, refresh_line);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief Sets signal handlers for non-interactive mode. Both SIGINT (Ctrl-C)
 * and SIGQUIT (Ctrl-\) display a new line and, for SIGQUIT, print a "Core
 * Dump" message.
 */

void	signals_non_interactive_handler(void)
{
	signal(SIGINT, display_new_line);
	signal(SIGQUIT, display_new_line);
}
