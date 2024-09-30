/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:59:13 by vados-sa          #+#    #+#             */
/*   Updated: 2024/09/30 15:00:56 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*utility function for export*/
void	print_env_var(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		printf("declare -x %s\n", data->env[i]);
		i++;
	}
}

void	copy_env_vars(char **new_env, char **old_env, int env_size)
{
	int	i;

	i = 0;
	while (i < env_size)
	{
		new_env[i] = old_env[i];
		i++;
	}
}