/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanessasantos <vanessasantos@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:06:36 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/07/03 17:01:19 by vanessasant      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <string.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_token
{
	char	*type;
	char	*value;
}	t_token;

typedef struct s_command
{
	char	*name;
	char	**args;
}	t_command;

typedef struct s_data
{
	char		**envp;
	int			input;
	int			output;
	t_token		token;
	t_command	command;
}	t_data;


/*signals.c ******************************************************************/
void	setup_signal_handlers();

#endif