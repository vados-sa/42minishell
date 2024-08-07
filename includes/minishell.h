/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:06:36 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/08/07 13:09:12 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define EXIT_SUCC 0
# define EXIT_FAIL 1
# define PIPE "|"
# define HEREDOC "<<"
# define APPEND ">>"
# define INPUT "<"
# define OUTPUT ">"
# define STDIN "IN"
# define STDOUT "OUT"
# define OTHERS "CFA" //comand-flag-argument
# define SINGLE_Q '\''
# define DOUBLE_Q '\"'
# define PIPE_STX_ERROR "syntax error near unexpected token "
# define QUOTE_STX_ERROR "syntax error: unclosed quote "
# define OTHER_STX_ERROR "syntax error near unexpected token"

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
void		setup_signal_handlers();

/*1_lexer*********************************************************************/
int			lex(t_data *data);
int			check_input(char *cpy_arg);
int			tokenize(t_data *data, char *cpy_arg);
int			look_for_operator(char c);
int			look_for_quotes(char c);
int			unclosed_quotes(char *input);
int			check_double_operator(char *arg);
int			assign_type_redirection(char *arg, char **type);
int			handle_redirection(char *arg, t_token **token);
int			handle_operator(t_data *data, char *arg);
int			handle_quotes(t_data *data, char *arg);
int			handle_word(t_data *data, char *arg);
t_token		*create_token(int size_lengh, char *str, char *type, int type_quote);
void		create_token_list(t_data*data, t_token*new);

/*2_parser********************************************************************/

int			split_token(t_data *data);
int			open_redir_in(t_data *data, t_token *token, int flag);
int			open_redir_out(t_data *data, t_token *token, int flag);
int			split_others_token(t_data *data, t_token *token, int *create_new_command);
int			parse(t_data *data);
int			fill_node(t_command *node, t_token *token, char *flag);
int			add_new_list_node(t_list **lst, t_token *token);
t_command	*create_command_node(t_data *data);
void		create_command_list(t_data *data, t_command *new);
int			expand_var(char **str, t_data *data);

/*3_executer******************************************************************/


/*utils***********************************************************************/
int			print_error_code(char *message, char tkn, int exit_code);
int			perror_return_error(char *message);

#endif