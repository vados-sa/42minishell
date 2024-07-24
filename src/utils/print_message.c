/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:55:02 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/07/24 13:01:24 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int print_error_code(char *message, char tkn, int exit_code)
{
	printf("%s'%c'\n", message, tkn);
	return (exit_code);
}

/* #define TOKEN_SINTAX_ERROR "syntax error near unexpected token "
#define ERROR_EXIT 1
int main(void)
{
    char tkn = '|';
    return(print_exit_code(TOKEN_SINTAX_ERROR, tkn, ERROR_EXIT));
} */