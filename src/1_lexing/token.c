/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 20:37:38 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/07/27 22:24:24 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token(int size_lengh, char *str, char *type, int type_quote)
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

void	create_token_list(t_data*data, t_token*new)
{
	t_token	*last;

	last = ft_lst_last_mod(data->token);
	if (!last)
	{
		data->token = new;
		return ;
	}
	last->next = new;
}
