/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:15:40 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/07/16 14:33:00 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memmove(void*dest, const void*src, size_t len)
{
	size_t			i;
	unsigned char	*temp_dest;
	unsigned char	*temp_src;

	i = 0;
	temp_dest = (unsigned char *)dest;
	temp_src = (unsigned char *)src;
	if (!temp_dest && !temp_src)
		return (0);
	if (temp_src < temp_dest)
	{
		i = len;
		while (i-- > 0)
			temp_dest[i] = temp_src[i];
	}
	else
	{
		while (i < len)
		{
			temp_dest[i] = temp_src[i];
			i++;
		}
	}
	return (dest);
}
