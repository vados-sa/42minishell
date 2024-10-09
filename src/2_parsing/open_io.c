/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:07:02 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/10/09 17:44:26 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_redir_in(t_data *data, t_token *token, int flag)
{
	if (ft_strcmp(data->input_type, STDIN) != 0 \
		&& ft_strcmp(data->input_type, HEREDOC) != 0)
		close(data->input_fd);
	if (!token->value)
		return (print_error_code(OTHER_STX_ERROR, token->type[0], EXIT_FAIL));
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
		add_fd(data, data->input_fd);
	}
	return (EXIT_SUCC);
}

int	open_redir_out(t_data *data, t_token *token, int flag)
{
	if (ft_strcmp(data->output_type, STDOUT) != 0)
		close(data->output_fd);
	if (!token->value)
		return (print_error_code(OTHER_STX_ERROR, token->type[0], EXIT_FAIL));
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
	add_fd(data, data->output_fd);
	return (EXIT_SUCC);
}
