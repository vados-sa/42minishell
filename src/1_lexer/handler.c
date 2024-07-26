/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:36:22 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/07/26 16:57:09 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


t_token	*create_token(int size_lengh, char *str, char *type, char *type_quote)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		perror("failed to allocate memory");
		return (NULL);
	}
	if (size_lengh > 0)
	{
		token->value = malloc((size_lengh + 1) * sizeof(char));
		if (!token->value)
		{
			perror("failed to allocate memory"); //check necessity of freeing the token
			return (NULL);
		}
		ft_strlcpy(token->value, str, size_lengh + 1);
	}
	else
		token->value = NULL;
	token->type = type;
	token->type_quote = type_quote;
	token->next = NULL;
	return (token);
}

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
		if (arg[0] == '>')
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

int	handle_operator(t_data *data, char *arg, int pos)
{
	int		i;
	t_token	*token;

	i = 0;
	if (check_double_operator(arg[pos]))
		return (-1);
	if ((arg[pos] == '<' || arg[pos] == '>'))
		i += handle_redirection(&arg[pos], &token);
	if (arg[pos] == '|')
	{
		token = create_token(0, &arg[pos], PIPE, NULL); // type quote NULL or NONE?
		i++;
	}
	if (!token)
		return (-1); //check if it's correct
	//create list
	return (i);
}

int	handle_quotes(t_data *data, char *arg, int pos)
{
	char 	*end_quote;
	int		i;
	t_token	*token;

	i = pos;
	end_quote = arg;
	while (end_quote[i + 1] != arg[pos])
		i++;
	if (arg[pos] == '\"')
		token = create_token(i - pos, &arg[pos], OTHERS, SINGLE_Q);// check if it's correct
	else
		token = create_token(i - pos, &arg[pos], OTHERS, DOUBLE_Q);// check if it's correct
	if (!token)
		return (-1); //check if it's correct
	//create list
	return (i - pos);
}

int	handle_word(t_data *data, char *arg, int pos)
{
	int		i;
	t_token	*token;

	i = pos;
	while (arg[i] || !ft_isspace(arg[i]) || !look_for_operator(arg[i]))
		i++;
	token = create_token(i - pos, &arg[pos], OTHERS, NULL);
	if (!token)
		return (-1); //check if it's correct
	//create list
	return (i - pos);
}
