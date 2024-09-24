/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 23:20:43 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/24 15:59:56 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*find_path(char *str, t_data *data)
{
	size_t	i;

	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(str, data->env[i], ft_strlen(str)))
			return (data->env[i]);
		i++;
	}
	return (NULL);
}

static char	*set_new_path(t_command *cmd, t_data *data)
{
	size_t	i;

	i = 0;
	if (!cmd->arguments)
	{
		while (data->env[i])
		{
			if (!ft_strncmp("HOME=", data->env[i], 5))
				return (data->env[i] + 5);
			i++;
		}
		printf("minishell: HOME directory not found in env\n");
		return (NULL);
	}
	else
		return (cmd->arguments->content);
}

int	rewrite_path(char *str, char *pwd, t_data *data)
{
	size_t	i;

	i = 0;
	while (ft_strncmp(data->env[i], str, ft_strlen(str)))
		i++;
	free(data->env[i]);
	data->env[i] = ft_strjoin(str, pwd);
	if (!data->env[i])
		return (perror_return_error("minishell: rewrite_path: realloc"));
	return (EXIT_SUCC);
}

static int	update_env(char *new_pwd, char *old_pwd, t_data *data)
{
	if (find_path("PWD=", data))
	{
		if (rewrite_path("PWD=", new_pwd, data))
			return (EXIT_FAIL);
	}
	else if (find_path("OLDPWD=", data))
	{
		if (rewrite_path("OLDPWD=", old_pwd, data))
			return (EXIT_FAIL);
	}
	return (EXIT_SUCC);
}

int	builtin_cd(t_command *cmd, t_data *data)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];
	char	*path;

	if (cmd->flags || (cmd->arguments && ft_lstsize(cmd->arguments) > 1))
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (EXIT_FAIL);
	}
	if (!getcwd(old_pwd, sizeof(old_pwd)))
		return (perror_return_error("getcwd() fail"));
	path = set_new_path(cmd, data);
	if (!path)
		return (EXIT_FAIL);
	if (chdir(path))
		return (perror_return_error("minishell: cd"));
	if (!getcwd(new_pwd, sizeof(new_pwd)))
		return (perror_return_error("getcwd() error"));
	if (update_env(new_pwd, old_pwd, data))
		return (EXIT_FAIL);
	return (EXIT_SUCC);
}
