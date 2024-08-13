/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arg_for_export.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:37:06 by vados-sa          #+#    #+#             */
/*   Updated: 2024/08/12 16:25:28 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_export_builtin_arg(t_command *cmd_node, t_token *token)
{
	int	i;

	i = 0; 
	if (!ft_isalpha(token->value[i]) && token->value[i] != '_') // invalid indetifier error
	{
		printf("bash: export: `%s': not a valid identifier\n", token->value);
		return (EXIT_FAILURE);
	}
	while (token->value[i]) // FIND '=' OR 'space'
	{
		if (token->value[i] == '=')
			break ;
		else if (!ft_isalnum(token->value[i]) && token->value[i] != '_')
			return (EXIT_FAILURE); // invalid identifier error
		i++;
	}
	if (token->value[i])
		; // save variable with no value to be exported -> I don't fully understand this yet
	else if (token->value[i] == '=')
	{
		; //save the variable name -> save node
		i++;
		//save 2nd node, value of the variable.
	}
	return (EXIT_SUCCESS);
}