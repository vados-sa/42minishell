/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:06:36 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/07/09 15:50:16 by vados-sa         ###   ########.fr       */
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
	char	*type; //typedef enum struct?
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
	char		*i_str;
	int			input;
	int			output;
	t_token		token;
	t_command	command;
}	t_data;


/*signals.c ******************************************************************/
void	setup_signal_handlers();

#endif