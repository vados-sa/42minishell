/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 23:20:43 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/03 17:11:29 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	builtin_export(t_command *cmd, t_data *data)
{
	
}


// CHECK FOR INVALID IDENTIFIERS
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