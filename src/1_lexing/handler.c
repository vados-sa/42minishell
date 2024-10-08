/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:36:22 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/10/08 19:06:12 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	assign_type_redirection(char *arg, char **type)
{
	if (arg[0] == arg[1])
	{
		if (arg[0] == '<')
			*type = HEREDOC;
		else
			*type = APPEND;
		return (2);
	}
	else
	{
		if (arg[0] == '<')
			*type = INPUT;
		else
			*type = OUTPUT;
		return (1);
	}
}

int	handle_redirection(char *arg, t_token **token)
{
	char	*type;
	int		type_quote;
	int		i;
	int		start;

	type_quote = 0;
	i = assign_type_redirection(arg, &type);
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == SINGLE_Q || arg[i] == DOUBLE_Q)
	{
		type_quote = arg[i];
		i++;
	}
	start = i;
	while (arg[i] && ((type_quote == SINGLE_Q || type_quote == DOUBLE_Q) \
		|| !ft_isspace(arg[i])) && !ft_strchr("<|>", arg[i])
		&& !((type_quote == SINGLE_Q && arg[i] == SINGLE_Q) \
		|| (type_quote == DOUBLE_Q && arg[i] == DOUBLE_Q)))
		i++;
	*token = create_token(i - start, &arg[start], type, type_quote);
	if (type_quote)
		i++;
	return (i);
}

int	handle_operator(t_data *data, char *arg)
{
	int		i;
	t_token	*token;

	i = 0;
	if (check_double_operator(&arg[i]))
		return (-1);
	if ((arg[i] == '<' || arg[i] == '>'))
		i += handle_redirection(&arg[i], &token);
	else if (arg[i] == '|')
	{
		token = create_token(0, &arg[0], PIPE, 0);
		i++;
	}
	if (!token)
		return (-1);
	create_token_list(data, token);
	return (i);
}

int	handle_quotes(t_data *data, char *arg)
{
	int		i;
	t_token	*token;

	i = 0;
	i += outer_quote(arg);
	if (arg[0] == '\"')
		token = create_token(i - 1, &arg[1], OTHERS, DOUBLE_Q);
	else
		token = create_token(i - 1, &arg[1], OTHERS, SINGLE_Q);
	if (!token)
		return (-1);
	create_token_list(data, token);
	return (i + 1);
}

int	handle_word(t_data *data, char *arg)
{
	int		i;
	t_token	*token;
	char	quote;

	i = 0;
	quote = 0;
	while (arg[i] && (!ft_isspace(arg[i]) || quote) && \
			!look_for_operator(arg[i]))
	{
		if (look_for_quotes(arg[i]))
		{
			if (!quote)
				quote = arg[i];
			else if (arg[i] == quote)
				quote = 0;
		}
		i++;
	}
	token = create_token(i, &arg[0], OTHERS, 0);
	if (!token)
		return (-1);
	create_token_list(data, token);
	return (i);
}
