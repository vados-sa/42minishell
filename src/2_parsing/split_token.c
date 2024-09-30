/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:00:51 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/30 14:12:52 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	split_token(t_data *data)
{
	t_token	*token;
	int		create_new_command;
	int		exit_s;

	token = data->token;
	create_new_command = 1;
	while (token)
	{
		exit_s = 0;
		if (token->type[0] == '<')
			exit_s = open_redir_in(data, token, O_RDONLY);
		else if (ft_strcmp(token->type, OUTPUT) == 0)
			exit_s = open_redir_out(data, token, O_WRONLY | O_TRUNC | O_CREAT);
		else if (ft_strcmp(token->type, APPEND) == 0)
			exit_s = open_redir_out(data, token, O_WRONLY | O_APPEND | O_CREAT);
		else if (ft_strcmp(token->type, OTHERS) == 0)
			exit_s = split_others_token(data, token, &create_new_command);
		else
			create_new_command = 1;
		if (exit_s)
			return (EXIT_FAIL);
		token = token->next;
	}
	return (EXIT_SUCC);
}

static int	handle_new_command(t_data *data, t_token *token, int *add_new_cmd,
						t_command **command)
{
	*add_new_cmd = 0;
	*command = create_command_node(data);
	if (!*command)
		return (EXIT_FAIL);
	if (fill_node(*command, token, "COMMAND"))
		return (EXIT_FAIL);
	return (EXIT_SUCC);
}

//check if possible to remove quotes in the argument
int	split_others_token(t_data *data, t_token *token, int *add_new_cmd)
{
	static t_command	*command;

	if (!token->value)
		return (EXIT_SUCC);
	if (*add_new_cmd)
	{
		if (handle_new_command(data, token, add_new_cmd, &command))
			return (EXIT_FAIL);
	}
	else if (token->value[0] == '-' && !ft_isspace(token->value[1]) && \
			token->value[1])
	{
		remove_possible_quotes(token->value);
		if (fill_node(command, token, "FLAG"))
			return (EXIT_FAIL);
	}
	else
	{
		if (fill_node(command, token, "ARGUMENT"))
			return (EXIT_FAIL);
	}
	return (EXIT_SUCC);
}
