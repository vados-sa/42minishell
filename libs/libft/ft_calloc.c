/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:38:32 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/07/16 14:29:20 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_calloc(size_t number, size_t size)
{
	void	*dest;

	dest = (void *)malloc(number * size);
	if (dest == 0)
		return (0);
	ft_bzero(dest, number * size);
	return (dest);
}
