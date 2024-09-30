/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:08:54 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/30 15:38:31 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*join_paths_and_command(char *path, char *command)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, command);
	free(temp);
	return (result);
}

static char	**get_paths(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	while (ft_strncmp("PATH", env[i], 4))
		i++;
	paths = ft_split(env[i] + 5, ':');
	return (paths);
}

char	*get_cmd_path(t_command *cmd, char **env)
{
	char	**paths;
	char	*result;
	int		i;

	paths = get_paths(env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		result = join_paths_and_command(paths[i], cmd->command);
		if (result && access(result, F_OK | X_OK) == 0)
		{
			free_double_pointer_char(&paths);
			return (result);
		}
		free(result);
		i++;
	}
	free_double_pointer_char(&paths);
	return (NULL);
}
