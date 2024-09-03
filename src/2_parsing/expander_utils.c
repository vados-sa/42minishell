/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:23:36 by vados-sa          #+#    #+#             */
/*   Updated: 2024/09/03 17:23:37 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_var_len(char *str)
{
	int	i;
	int	len;

	i = 1;
	len = 0;
	if (str[1] == '{')
		i++;
	if (str[i] == '?')
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_') && str[i] != '}')
	{
		len++;
		i++;
	}
	return (len);
}

char	*get_exp_env(char *str, int len, char **env_arg)
{
	if (!env_arg)
	{
		printf("Environment variable array is NULL\n");
		return ("");
	}
	while (*env_arg)
	{
		if (!ft_strncmp(str + 1, *env_arg, len) && (*env_arg)[len] == '=')
			return (*env_arg + len + 1);
		env_arg++;
	}
	return ("");
}

void	free_substr(char **s1, char **s2, char **s3)
{
	if (*s1)
	{
		free (*s1);
		*s1 = NULL;
	}
	if (*s2)
	{
		free (*s2);
		*s2 = NULL;
	}
	if (*s3)
	{
		free (*s3);
		*s3 = NULL;
	}
}
