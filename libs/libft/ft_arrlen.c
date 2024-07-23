/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:45:17 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/07/23 13:00:31 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdio.h>

size_t	ft_arrlen(char**arr)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (arr[i])
	{
		len = 0;
		while(arr[i][len] != '\0')
			len++;
		i++;
	}
	return (i);
}
