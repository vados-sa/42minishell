/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 20:37:38 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/08/24 19:43:33 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//check necessity of freeing the token -line 31
t_token	*create_token(int size_len, char *str, char *type, int type_quote)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		perror("failed to allocate memory");
		return (NULL);
	}
	if (size_len > 0)
	{
		token->value = malloc((size_len + 1) * sizeof(char));
		if (!token->value)
		{
			perror("failed to allocate memory");
			return (NULL);
		}
		ft_strlcpy(token->value, str, size_len + 1);
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

	last = ft_lst_last_token(data->token);
	if (!last)
	{
		data->token = new;
		return ;
	}
	last->next = new;
}
