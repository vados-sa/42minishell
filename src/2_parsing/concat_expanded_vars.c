/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat_expanded_vars.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:24:45 by vados-sa          #+#    #+#             */
/*   Updated: 2024/09/03 17:25:52 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*find_after_var(char *str, int var_len)
{
	int		i;
	char	*after_var;

	i = 0;
	if (str[i + 1] == '{')
		after_var = ft_substr(str, i + var_len + 3, ft_strlen(str) - \
					(var_len + 1) - (i + 1));
	else
		after_var = ft_substr(str, i + var_len + 1, ft_strlen(str) - \
					var_len - i);
	return (after_var);
}

static char	*find_exp_var(char *str, int var_len, t_data *data)
{
	int		i;
	char	*exp_var;

	i = 0;
	if (str[i + 1] == '?' || (str[i + 1] == '{' && str[i + 2] == '?'))
		exp_var = ft_itoa(data->exit_status);
	else if (str[i + 1] == '{')
		exp_var = ft_strdup(get_exp_env(&str[i + 1], var_len, data->env));
	else
		exp_var = ft_strdup(get_exp_env(&str[i], var_len, data->env));
	return (exp_var);
}

static char	*ft_concat(char *s1, char *s2, char *s3)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, s3);
	free (temp);
	if (!result)
		return (NULL);
	return (result);
}

char	*concat_expanded_var(char **str, int *i, t_data *data)
{
	int		len;
	char	*before_var;
	char	*after_var;
	char	*exp_var;
	char	*exp_str;

	len = env_var_len(&(*str)[*i]);
	if (!len)
		return (NULL);
	before_var = ft_substr(*str, 0, *i);
	after_var = find_after_var(&(*str)[*i], len);
	exp_var = find_exp_var(&(*str)[*i], len, data);
	*i += ft_strlen(exp_var) + 1; //check if +1 is not giving any issues
	exp_str = ft_concat(before_var, exp_var, after_var);
	free_substr(&before_var, &exp_var, &after_var);
	if (!exp_str)
		return (NULL);
	return (exp_str);
}