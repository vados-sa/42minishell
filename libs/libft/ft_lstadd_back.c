/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:36:38 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/07/16 14:32:01 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstadd_back(t_list**lst, t_list*new)
{
	t_list	*last;

	last = ft_lst_last(*lst);
	if (!last)
	{
		*lst = new;
		return ;
	}
	last -> next = new;
}
