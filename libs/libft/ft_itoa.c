/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:48:40 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/07/16 14:30:22 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	n_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static long int	abs_value(int n)
{
	long int	nb;

	nb = 1;
	if (n < 0)
		nb *= -n;
	else
		nb *= n;
	return (nb);
}

char	*ft_itoa(int n)
{
	unsigned int		nb;
	int					sign;
	int					len;
	char				*dest;

	sign = 0;
	if (n < 0)
		sign = 1;
	len = n_len(n);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (0);
	dest[len] = '\0';
	nb = abs_value(n);
	while (len > 0)
	{
		dest[len - 1] = '0' + nb % 10;
		nb /= 10;
		len--;
	}
	if (sign == 1)
		dest[0] = '-';
	return (dest);
}
