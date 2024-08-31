/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 23:20:43 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/08/31 16:57:53 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	find_path(char *str, char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(str, env[i], ft_strlen(str)))
			return (1);
		i++;
	}
	return (0);
}

static char	*set_new_path(t_command *cmd, char **env)
{
	size_t	i;

	i = 0;
	if (!cmd->arguments)
	{
		while (env[i])
		{
			if (!ft_strncmp("HOME=", env[i], 5))
				return (env[i] + 5);
			i++;
		}
		printf("minishell: HOME directory not found in env\n");
		return (NULL);
	}
	else
		return (cmd->arguments->content);
}

int	rewrite_path(char *str, char *pwd, char **env)
{
	size_t	i;

	i = 0;
	while (ft_strncmp(env[i], str, ft_strlen(str)))
		i++;
	free(env[i]);
	env[i] = ft_strjoin(str, pwd);
	if (!env[i])
		return (perror_return_error("minishell: rewrite_path: realloc"));
	return (EXIT_SUCC);
}

static int	update_env(char *new_pwd, char *old_pwd, char **env)
{
	if (find_path("PWD=", env))
	{
		if (rewrite_path("PWD=", new_pwd, env))
			return (EXIT_FAIL);
	}
	else if (find_path("OLDPWD=", env))
	{
		if (rewrite_path("OLDPWD=", old_pwd, env))
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
		ft_putstr_fd("minishell: cd only support one argument\n", 1); //check if it is 1 or 2
		return (EXIT_FAIL);
	}
	if (!getcwd(old_pwd, sizeof(old_pwd)))
		return (perror_return_error("getcwd() fail"));
	path = set_new_path(cmd, data->env);
	if (!path)
		return (EXIT_FAIL);
	if (chdir(path))
		return (perror_return_error("chdir() fail"));
	if (!getcwd(new_pwd, sizeof(new_pwd)))
		return (perror_return_error("getcwd() error"));
	if (update_env(new_pwd, old_pwd, data->env))
		return (EXIT_FAIL);
	return (EXIT_SUCC);
}
