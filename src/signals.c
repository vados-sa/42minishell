#include "../includes/minishell.h"

static void signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0); // Clear the current input line
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line(); // Move the cursor to a new line
        rl_redisplay(); // Redisplay the prompt
	}
	// I'm guessing that for Ctrl-D a function that cleans and quits the program is called
}

void	setup_signal_handlers()
{
	signal(SIGINT, signal_handler); // SIGINT is triggered by 'Ctrl-C'
	signal(SIGQUIT, SIG_IGN); // Ignore 'Ctrl-\'
}
