/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:10:50 by vados-sa          #+#    #+#             */
/*   Updated: 2024/09/30 13:14:31 by vados-sa         ###   ########.fr       */
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

int	open_redir_in(t_data *data, t_token *token, int flag)
{
	if (ft_strcmp(data->input_type, STDIN) != 0 \
		&& ft_strcmp(data->input_type, HEREDOC) != 0)
		close(data->input_fd);
	data->input_value = ft_strdup(token->value);
	if (!data->input_value)
		return (perror_return_error("redirection value"));
	data->input_type = token->type;
	data->input_type_quote = token->type_quote;
	if (token->type_quote != '\'')
		expand_var(&token->value, data);
	if (ft_strcmp(data->input_type, HEREDOC) != 0)
	{
		data->input_fd = open(data->input_value, flag, 0644);
		if (data->input_fd < 0)
			return (perror_return_error(data->input_value));
	}
	return (EXIT_SUCC);
}

int	open_redir_out(t_data *data, t_token *token, int flag)
{
	if (ft_strcmp(data->output_type, STDOUT) != 0)
		close(data->output_fd);
	data->output_value = ft_strdup(token->value);
	if (!data->output_value)
		return (perror_return_error("redirection value"));
	data->output_type = token->type;
	data->output_type_quote = token->type_quote;
	if (token->type_quote != '\'')
		expand_var(&token->value, data);
	data->output_fd = open(data->output_value, flag, 0644);
	if (!data->output_fd)
		return (perror_return_error(data->output_value));
	return (EXIT_SUCC);
}

int	split_others_token(t_data *data, t_token *token, int *add_new_cmd)
{
	static t_command	*command;

	if (!token->value)
		return (EXIT_SUCC);
	if (*add_new_cmd)
	{
		*add_new_cmd = 0;
		command = create_command_node(data);
		if (!command)
			return (EXIT_FAIL);
		if (fill_node(command, token, "COMMAND"))
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
		//remove_possible_quotes(token->value); // cannot be here -> CHECK WHEN TO REMOVE
		if (fill_node(command, token, "ARGUMENT"))
			return (EXIT_FAIL);
	}
	return (EXIT_SUCC);
}

static int	remove_empty_initial_tokens(t_data *data)
{
	t_command	*cmd;
	t_command	*prev;
	t_command	*temp;
	t_list		*tmp_arg;

	cmd = data->command;
	prev = NULL;
	while (cmd)
	{
		while (cmd->command && cmd->command[0] == '\0')
		{
			free(cmd->command);
			if (cmd->arguments)
			{
				cmd->command = ft_strdup(cmd->arguments->content);
				tmp_arg = cmd->arguments;
				cmd->arguments = cmd->arguments->next;
				free(tmp_arg->content);
				free(tmp_arg);
			}
			else
			{
				cmd->command = NULL;
				break ;
			}
		}
		if (!cmd->command && !cmd->arguments && !cmd->flags)
		{
			temp = cmd;
			if (prev)
				prev->next = cmd->next;
			else
				data->command = cmd->next;
			cmd = cmd->next;
			free(temp->command);
			free_list(temp->arguments);
			free_list(temp->flags);
			free(temp);
		}
		else
		{
			prev = cmd;
			cmd = cmd->next;
		}
	}
	return (EXIT_SUCC);
}

int	parse(t_data *data)
{
	if (split_token(data))
		return (EXIT_FAIL);
	if (expand_tokens(data))
		return (EXIT_FAIL);
	if (remove_empty_initial_tokens(data))
		return (EXIT_FAIL);
	if (organize_final_cmd_array(data))
		return (EXIT_FAIL);
	if (ft_strcmp(data->input_type, HEREDOC) == 0)
	{
		if (handle_heredoc(data))
			return (EXIT_FAIL);
	}
	return (EXIT_SUCC);
}
