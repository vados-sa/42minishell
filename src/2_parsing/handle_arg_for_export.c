/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arg_for_export.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:37:06 by vados-sa          #+#    #+#             */
/*   Updated: 2024/08/14 18:57:08 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_export_builtin_arg(t_command *cmd_node, t_token *token)
{
	
	return (EXIT_SUCCESS);
}

// CHECK FOR INVALID IDENTIFIERS
// this may go in the execution part.
/* if (!ft_isalpha(token->value[i]) && token->value[i] != '_') // invalid indetifier error
	{
		printf("bash: export: `%s': not a valid identifier\n", token->value);
		return (EXIT_FAILURE);
	}
	while (token->value[i] || token->value[i] != '=') // FIND '=' OR 'space'
	{
		if (!ft_isalnum(token->value[i]) && token->value[i] != '_')
			return (EXIT_FAILURE); // invalid identifier error
		i++;
	} */