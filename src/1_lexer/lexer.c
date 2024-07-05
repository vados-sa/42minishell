/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:09:51 by vados-sa          #+#    #+#             */
/*   Updated: 2024/07/05 16:59:30 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    lexical_analysis(t_data *data, char *input)
{
	
}

int main(void)
{
	char *rl;
	t_data  *data;

	rl = "grep -i 'search term' < input.txt | sort > output.txt";
	lexical_analysis(data, rl);
	return (0);
}