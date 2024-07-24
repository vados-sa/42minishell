/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:06:36 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/07/24 13:01:16 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define TOKEN_SINTAX_ERROR "syntax error near unexpected token "

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

# include "../includes/libft.h"
# include "../includes/get_next_line.h"
# include "../includes/structures.h"

/*signals.c ******************************************************************/
void	setup_signal_handlers();

/*1_lexer*********************************************************************/


/*2_parser********************************************************************/


/*3_executer******************************************************************/


/*utils***********************************************************************/
int		print_error_code(char *message, char tkn, int exit_code);

#endif