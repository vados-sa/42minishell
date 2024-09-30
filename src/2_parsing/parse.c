/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:10:50 by vados-sa          #+#    #+#             */
/*   Updated: 2024/09/30 14:09:09 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	remove_first_argument(t_command *cmd)
{
	t_list	*tmp_arg;

	tmp_arg = cmd->arguments;
	cmd->arguments = cmd->arguments->next;
	free(tmp_arg->content);
	free(tmp_arg);
}

static void	remove_command(t_command **cmd, t_command **prev, t_data *data)
{
	t_command	*temp;

	temp = *cmd;
	if (*prev)
		(*prev)->next = (*cmd)->next;
	else
		data->command = (*cmd)->next;
	*cmd = (*cmd)->next;
	free(temp->command);
	free_list(temp->arguments);
	free_list(temp->flags);
	free(temp);
}

static int	remove_empty_initial_tokens(t_data *data)
{
	t_command	*cmd;
	t_command	*prev;

	cmd = data->command;
	prev = NULL;
	while (cmd)
	{
		while (cmd->command && cmd->command[0] == '\0')
		{
			if (!cmd->arguments)
				break ;
			free(cmd->command);
			cmd->command = ft_strdup(cmd->arguments->content);
			remove_first_argument(cmd);
		}
		if (!cmd->command && !cmd->arguments && !cmd->flags)
			remove_command(&cmd, &prev, data);
		else
		{
			prev = cmd;
			cmd = cmd->next;
		}
	}
	return (EXIT_SUCC);
}

int	parse(t_data *data)
{
	if (split_token(data))
		return (EXIT_FAIL);
	if (expand_tokens(data))
		return (EXIT_FAIL);
	if (remove_empty_initial_tokens(data))
		return (EXIT_FAIL);
	if (organize_final_cmd_array(data))
		return (EXIT_FAIL);
	if (ft_strcmp(data->input_type, HEREDOC) == 0)
	{
		if (handle_heredoc(data))
			return (EXIT_FAIL);
	}
	return (EXIT_SUCC);
}
