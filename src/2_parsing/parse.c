/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:10:50 by vados-sa          #+#    #+#             */
/*   Updated: 2024/08/05 17:17:38 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parse(t_data *data)
{
	
	if (!split_token(data))
		return (EXIT_FAIL);
	//expand
	//handle heredoc
	return (EXIT_SUCC);
}

int	split_token(t_data *data)
{
	t_token	*token;
	int		create_new_command;
	int		exit_s;

	token = data->token;
	create_new_command = 1;
	while (token)
	{
		if (token->type == INPUT || token->type == HEREDOC)
			exit_s = open_redir_in(data, token, O_RDONLY);
		else if (token->type == OUTPUT)
			exit_s = open_redir_out(data, token, O_WRONLY | O_TRUNC | O_CREAT);
		else if (token->type == APPEND)
			exit_s = open_redir_out(data, token, O_WRONLY | O_APPEND | O_CREAT);
		else if (token->type == OTHERS)
			exit_s = split_others_token(data, token, &create_new_command);
		else
			create_new_command = 1;
		if (exit_s)
			return (EXIT_FAIL);
		token = token->next;
	}
	return (EXIT_SUCC);
}

void	expand_var(void)
{
	
}

int	open_redir_in(t_data *data, t_token *token, int flag)
{
	if (data->input_type != STDIN_FILENO && data->input_type != HEREDOC)
		close(data->input_fd);
	data->input_value = ft_strdup(token->value);
	if (!data->input_value)
		return (perror_return_error("redirection value"));
	data->input_type = token->type;
	data->input_type_quote = token->type_quote;
	if (token->type_quote != '\'')
		;// expand_var(data, )
	if (data->input_type != HEREDOC)
	{
		data->input_fd = open(data->input_value, flag, 0644);
		if (data->input_fd < 0)
			return (perror_return_error(data->input_fd));
	}
	return (EXIT_SUCC);
}

int	open_redir_out(t_data *data, t_token *token, int flag)
{
	if (data->output_type != STDOUT_FILENO)
		close(data->output_fd);
	data->output_value = ft_strdup(token->value);
	if (!data->output_value)
		return (perror_return_error("redirection value"));
	data->output_type = token->type;
	data->output_type_quote = token->type_quote;
	if (token->type_quote != '\'')
		;// expand_var(data, )
	data->output_fd = open(data->output_value, flag, 0644);
	if (!data->output_fd)
		return (perror_return_error(data->output_fd));
	return (EXIT_SUCC);
}

int	split_others_token(t_data *data, t_token *token, int *create_new_command)
{
	static t_command	*command;

	if (*create_new_command)
	{
		*create_new_command = 0;
		command = create_command_node(data);
		if (!command)
			return (EXIT_FAIL);
		if (fill_node(command, token, 'COMMAND'))
			return (EXIT_FAIL);
	}
	else if (token->value[0] == '-')
	{
		if (fill_node(command, token, 'FLAG'))
			return (EXIT_FAIL);
	}
	else
	{
		if (fill_node(command, token, 'ARGUMENT'))
			return (EXIT_FAIL);
	}
	return (EXIT_SUCC);
}
