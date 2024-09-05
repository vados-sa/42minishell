/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:13:36 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/05 14:53:28 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_double_pointer_char(char**str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

void	free_double_pointer_int(int**n)
{
	int	i;

	i = 0;
	if (n)
	{
		while (n[i])
		{
			free(n[i]);
			i++;
		}
		free(n);
	}
}

void	free_substr(char **s1, char **s2, char **s3)
{
	if (*s1)
	{
		free (*s1);
		*s1 = NULL;
	}
	if (*s2)
	{
		free (*s2);
		*s2 = NULL;
	}
	if (*s3)
	{
		free (*s3);
		*s3 = NULL;
	}
}
