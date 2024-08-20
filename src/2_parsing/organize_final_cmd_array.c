/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_final_cmd_array.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:29:54 by vados-sa          #+#    #+#             */
/*   Updated: 2024/08/20 16:57:42 by vados-sa         ###   ########.fr       */
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
		i++;
	}
    free(final_av);
}

static int	add_command_to_array(long *i, t_command *cmd_ptr)
{
	cmd_ptr->final_av[*i] = ft_strdup(cmd_ptr->command);
	if (!cmd_ptr->final_av[*i])
		return (perror_return_error("add_command_to_array malloc"));
	(*i)++;
	return (EXIT_SUCCESS);
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
	return (EXIT_SUCCESS);
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
	return (EXIT_SUCCESS);
}

long	get_nbr_of_elements(t_command *cmd_node)
{
	long		count;
	t_list		*args;
	t_list		*flags;
	
	count = 1;
	args = cmd_node->arguments;
	flags = cmd_node->flags;
	while (cmd_node)
	{		
		while(args)
		{
			count++;
			args = args->next;
		}
		while (flags)
		{
			count++;
			flags = flags->next;
		}
		cmd_node = cmd_node->next;
	}
	return (count);
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
			return (EXIT_FAILURE);
		cmd_ptr->final_av[i] = NULL;
		cmd_ptr = cmd_ptr->next;
	}
	return (EXIT_SUCCESS);
}
