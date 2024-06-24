/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanessasantos <vanessasantos@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:17:19 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/06/24 14:32:25 by vanessasant      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	// Initialize
    char    *rl;
    char    *pwd;

    pwd = getcwd(NULL, 0);
    printf("pwd: %s\n", pwd);
    // Interpret
    while (1)
    {
        rl = readline("minishell> ");
        if (rl == NULL)
        {
            printf("\n");
            break ;
        }
        printf("%s\n", rl);
        add_history(rl);
        free(rl);
    }
    // Terminate
    return (EXIT_SUCCESS);
}
