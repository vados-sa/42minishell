/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_final_cmd_array.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:29:54 by vados-sa          #+#    #+#             */
/*   Updated: 2024/09/30 13:13:50 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_final_array(char **final_av, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(final_av[i]);
		final_av[i] = NULL;
		i++;
	}
	free(final_av);
	final_av = NULL;
}

static int	add_command_to_array(long *i, t_command *cmd_ptr)
{
	cmd_ptr->final_av[*i] = ft_strdup(cmd_ptr->command);
	if (!cmd_ptr->final_av[*i])
		return (perror_return_error("add_command_to_array malloc"));
	(*i)++;
	return (EXIT_SUCC);
}

static int	add_args_to_array(long *i, t_command *cmd_ptr)
{
	t_list	*arguments;

	arguments = cmd_ptr->arguments;
	while (arguments)
	{
		cmd_ptr->final_av[*i] = ft_strdup(arguments->content);
		if (!cmd_ptr->final_av[*i])
		{
			free_final_array(cmd_ptr->final_av, *i);
			return (perror_return_error("add_args_to_array malloc"));
		}
		(*i)++;
		arguments = arguments->next;
	}
	return (EXIT_SUCC);
}

static int	add_flags_to_array(long *i, t_command *cmd_ptr)
{
	t_list	*flags;

	flags = cmd_ptr->flags;
	while (flags)
	{
		cmd_ptr->final_av[*i] = ft_strdup(flags->content);
		if (!cmd_ptr->final_av[*i])
		{
			free_final_array(cmd_ptr->final_av, *i);
			return (perror_return_error("add_flags_to_array malloc"));
		}
		(*i)++;
		flags = flags->next;
	}
	return (EXIT_SUCC);
}

int	organize_final_cmd_array(t_data *data)
{
	t_command	*cmd_ptr;
	long		nbr_of_elements;
	long		i;

	cmd_ptr = data->command;
	while (cmd_ptr)
	{
		nbr_of_elements = get_nbr_of_elements(cmd_ptr);
		cmd_ptr->final_av = malloc(sizeof(char *) * (nbr_of_elements + 1));
		if (!cmd_ptr->final_av)
			return (perror_return_error("Final argv malloc failed"));
		i = 0;
		if (add_command_to_array(&i, cmd_ptr)
			|| add_args_to_array(&i, cmd_ptr)
			|| add_flags_to_array(&i, cmd_ptr))
			return (EXIT_FAIL);
		cmd_ptr->final_av[i] = NULL;
		cmd_ptr = cmd_ptr->next;
	}
	return (EXIT_SUCC);
}
