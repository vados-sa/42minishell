/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:29:30 by vados-sa          #+#    #+#             */
/*   Updated: 2024/09/05 15:29:16 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	expand_var(char **str, t_data *data)
{
	int		i;
	char 	*temp;
	
	i = 0;
	temp = NULL;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			temp = concat_expanded_var(str, &i, data);
			if (!temp)
				return (EXIT_FAILURE);
			free(*str);
			*str = temp;
		}
		else
			i++;
	}
	return (EXIT_SUCCESS);
}

static int	expand_command(t_command *cmd_node, t_data *data)
{
	while (cmd_node)
	{
		if (cmd_node->type_quote != '\'')
		{
			if (expand_var(&cmd_node->command, data))
				return (EXIT_FAILURE);
		}
		cmd_node = cmd_node->next;
	}
	return (EXIT_SUCCESS);
}

static int	expand_list_of_str(t_list *list, t_data *data)
{
	while (list)
	{
		if (list->type_quote != '\'')
		{
			if (expand_var(&list->content, data))
				return (EXIT_FAILURE);
		}
		list = list->next;
	}
	return (EXIT_SUCCESS);
}

int	expand_tokens(t_data *data)
{
	t_command	*current_cmd_node;

	current_cmd_node = data->command;
	while (current_cmd_node)
	{
		if (expand_command(current_cmd_node, data))
			return (EXIT_FAILURE);
		if (expand_list_of_str(current_cmd_node->arguments, data))
			return (EXIT_FAILURE);
		if (expand_list_of_str(current_cmd_node->flags, data))
			return (EXIT_FAILURE);
		current_cmd_node = current_cmd_node->next;
	}
	return (EXIT_SUCCESS);
}
/* int main()
{
    // Sample environment variables
    char *env[] = {
        "HOME=/home/user",
        "USER=vados-sa",
        "SHELL=/bin/bash",
        "PATH=/usr/bin:/bin",
        NULL
    };

	// Calculate the number of environment variables
    int env_count = 0;
    while (env[env_count]) {
        env_count++;
    }

	// Allocate memory for the data.env array
    t_data data;

	memset(&data, 0, sizeof(t_data));
	data.env = malloc((env_count + 1) * sizeof(char *));
	if (!data.env) {
        perror("malloc");
        return 1;
    }
	int i = 0;
	while (env[i])
	{
		data.env[i] = ft_strdup(env[i]);
		if (!data.env[i]) {
            perror("ft_strdup");
            return 1;
        }
		i++;
	}
	data.env[env_count] = NULL;
	data.input_fd = STDIN_FILENO;
	data.input_value = NULL;
	data.input_type = STDIN;
	data.output_fd = STDOUT_FILENO;
	data.output_value = NULL;
	data.output_type = STDOUT;
    data.exit_status = 42;

    // Test cases
    char *test_cases[] = {
        "$HOME/docs/file.txt",
		"${HOME}/docs/file.txt",
        "$USER is the current user",
		"${USER} is the current user",
        "The shell is $SHELL",
		"The shell is ${SHELL}",
        "Path is set to $PATH",
        "Path is set to ${PATH}",
        "Exit status was $?",
        "Exit status was ${?}",
        "Unknown variable $UNKNOWN",
        "Unknown variable ${UNKNOWN}",
        NULL
    };

	i = 0;
	while (test_cases[i])
	{
		char *input = strdup(test_cases[i]);
        printf("Original: %s\n", input);
        if (expand_var(&input, &data) == EXIT_SUCCESS)
            printf("Expanded: %s\n\n", input);
        else
            printf("Expansion failed\n\n");
        free(input);
		i++;
	}

    return 0;
} */