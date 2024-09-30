/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:06:36 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/30 15:36:58 by vados-sa         ###   ########.fr       */
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
# define OTHERS "CFA" // comand-flag-argument
# define SINGLE_Q 39 // int representation of \'
# define DOUBLE_Q 34 // int representation of \"
# define PIPE_STX_ERROR "syntax error near unexpected token "
# define QUOTE_STX_ERROR "syntax error: unclosed quote "
# define OTHER_STX_ERROR "syntax error near unexpected token"
//check macros above:
# define FD_E -1
# define FD_R 0
# define FD_W 1
# define FD_RW 2

# define PATH_MAX 4096

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
# include <dirent.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../includes/libft.h"
# include "../includes/get_next_line.h"
# include "../includes/structures.h"

/**main.c*********************************************************************/
void		minishell_loop(t_data *data);

/**init.c*********************************************************************/
int			init_data(t_data *data, char **env);

/**signals.c******************************************************************/
void		signals_non_interactive_handler(void);
void		signals_interactive_handler(void);

/*1_lexer*********************************************************************/
/**checker.c******************************************************************/
int			check_double_operator(char *arg);
int			check_input(char *cpy_arg);
int			unclosed_quotes(char *input);
int			outer_quote(char *arg);

/**handler.c******************************************************************/
int			assign_type_redirection(char *arg, char **type);
int			handle_redirection(char *arg, t_token **token);
int			handle_operator(t_data *data, char *arg);
int			handle_quotes(t_data *data, char *arg);
int			handle_word(t_data *data, char *arg);

/**lex.c**********************************************************************/
int			lex(t_data *data);
int			tokenize(t_data *data, char *cpy_arg);

/**token.c********************************************************************/
t_token		*create_token(int size_len, char *str, char *type, int type_quote);
void		create_token_list(t_data*data, t_token*new);

/*2_parser********************************************************************/
/**command.c******************************************************************/
int			fill_node(t_command *cmd_node, t_token *token, char *flag);
int			add_new_list_node(t_list **lst, t_token *token);
t_command	*create_command_node(t_data *data);
void		create_command_list(t_data *data, t_command *new);

/**concat_expanded_vars.c*****************************************************/
char		*concat_expanded_var(char **str, int *i, t_data *data);
char		*ft_concat(char *s1, char *s2, char *s3);

/**parser_utils.c***********************************************************/
int			env_var_len(char *str);
char		*get_exp_env(char *str, int len, char **env_arg);
void		remove_possible_quotes(char *str);
long		get_nbr_of_elements(t_command *cmd_node);

/**expander.c*****************************************************************/
int			expand_var(char **str, t_data *data);
int			expand_tokens(t_data *data);

/**handle_arg_for_export.c****************************************************/
int			open_quotes(t_command *cmd_node);
char		*get_equal_sign_pos(t_command *cmd_node);
int			concat_args(t_command *cmd_node, t_token *token, int *add_new_node);
int			handle_export_builtin_arg(t_command *cmd_node, t_token *token);

/**arg_for_export_utils.c*****************************************************/
void		closed_quote(char *str, int *add_new_node);

/**handle_heredoc.c***********************************************************/
void		get_all_file(int fd1, char *limiter);
int			handle_heredoc(t_data *data);

/**organize_final_cmd_array.c*************************************************/
int			organize_final_cmd_array(t_data *data);

/**parse.c****************************************************/
int			split_token(t_data *data);
int			open_redir_in(t_data *data, t_token *token, int flag);
int			open_redir_out(t_data *data, t_token *token, int flag);
int			split_others_token(t_data *data, t_token *token, int *add_new_cmd);
int			parse(t_data *data);

/*3_executer******************************************************************/
/*builtin_exec.c**************************************************************/
int			process_builtin(int **fds, int pos, t_command *cmd, t_data *data);
int			execute_builtin(t_command *cmd, t_data *data);
int			check_if_builtin(t_command *cmd);

/**command_exec.c**************************************************************/
int			process_not_builtin(int **fds, int pos, int *pid, t_data *data);
void		execute_command(t_command *cmd, t_data *data);
char		*get_cmd_path(t_command *cmd, char **env);

/**exec.c**********************************************************************/
int			exec(t_data*data);
void		child_exec(pid_t *id_p, int pos, t_data *data, int **fds);
int			processing(int **fds, pid_t *id_p, t_data *data);

/**pipe.c**********************************************************************/
int			**create_pipes(int qt_cmd);
void		close_fd(int *fd);
void		close_unused_fd(int **fds, int pos, int keep, int cmds_num);
int			redirect_io(int **fds, int pos, t_data *data, int cmds_num);

/**close_fd.c*****************************************************************/
void		close_unused_fd(int **fds, int pos, int keep, int cmds_num);
void		close_fd(int *fd);

/**builtins*******************************************************************/
/***cd.c**********************************************************************/
char		*find_path(char *str, t_data *data);
int			rewrite_path(char *str, char *pwd, t_data *data);
int			builtin_cd(t_command *cmd, t_data *data);

/***echo.c********************************************************************/
int			builtin_echo(t_command *cmd);

/***env.c*********************************************************************/
int			builtin_env(t_command *cmd, t_data *data);

/***exit.c********************************************************************/
void		minishell_exit(t_data *data, int exit_code, int flag);
int			builtin_exit(t_command *cmd, t_data*data);

/***export.c******************************************************************/
int			builtin_export(t_command *cmd, t_data *data);

/***pwd.c*********************************************************************/
int			builtin_pwd(t_command *cmd, t_data *data);

/***unset.c*******************************************************************/
int			builtin_unset(t_command *cmd, t_data *data);

/***bultin_utils.c************************************************************/
void		print_env_var(t_data *data);
void		copy_env_vars(char **new_env, char **old_env, int env_size);

/*utils***********************************************************************/
/**free.c*********************************************************************/
void		free_double_pointer_char(char ***str);
void		free_double_pointer_int(int**n, int qt_cmd);
void		free_substr(char **s1, char **s2, char **s3);
void		free_data(t_data *data);
void		free_env_and_path(t_data *data);

/*free_structures.c***********************************************************/
void		free_list(t_list *list);
void		free_commands(t_data *data);
void		free_tokens(t_data *data);

/**print_message.c************************************************************/
int			print_error_code(char *message, char tkn, int exit_code);
int			perror_return_error(char *message);
void		pe_status(t_data *data, char *cmd, char *message, int status);

/**utils.c********************************************************************/
int			look_for_operator(char c);
int			look_for_quotes(char c);
int			add_value_to_env(char *env_var, char *value, t_data *data);
int			check_invalid_identifiers(char *arg);

#endif
