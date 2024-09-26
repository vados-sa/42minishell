/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:29:30 by vados-sa          #+#    #+#             */
/*   Updated: 2024/09/26 18:26:42 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Checks whether the given index is inside single quotes in the string.
 *
 * Loops through the string up to the specified index to determine if the
 * current position is inside a pair of single quotes. Double quotes are
 * also considered, but only to ignore them while looking for single quotes.
 *
 * @param str The input string.
 * @param index The index where we check the quoting state.
 * @return 1 if inside single quotes, 0 otherwise.
 */
int	check_single_quote_state(char *str, int index) // solution for single quotes proble. should work, let's see
{
	int i;
	int inside_double_quotes;
	int inside_single_quotes;

	i = 0;
	inside_double_quotes = 0;
	inside_single_quotes = 0;
	while (i < index)
	{
		if (str[i] == '"' && !inside_single_quotes)
			inside_double_quotes = !inside_double_quotes;
		else if (str[i] == '\'' && !inside_double_quotes)
			inside_single_quotes = !inside_single_quotes;
		i++;
	}
	return (inside_single_quotes);
}

/**
 * @brief Expands environment variables within a string unless they are inside single quotes.
 *
 * Iterates through the string looking for '$' symbols. If the symbol is not inside
 * single quotes, the corresponding environment variable is expanded. The string
 * is updated in place with the expanded content.
 *
 * @param str The string containing potential variables to expand.
 * @param data The main data structure containing environment variables.
 * @return EXIT_SUCC on success, EXIT_FAIL on failure.
 */
int	expand_var(char **str, t_data *data)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while ((*str)[i])
	{
		if ((*str)[i] == '$' && (*str)[i + 1] && (*str)[i + 1] != ' ')
		{
			if (check_single_quote_state(*str, i) == 0)
			{
				temp = concat_expanded_var(str, &i, data);
				if (!temp)
					return (EXIT_FAIL);
				free(*str);
				*str = temp;
			}
			else
				i++;
		}
		else
			i++;
	}
	return (EXIT_SUCC);
}

/**
 * @brief Expands environment variables within command strings.
 *
 * Iterates through command nodes and expands any environment variables in the
 * command strings unless the command is enclosed in single quotes.
 *
 * @param cmd_node The command node to process.
 * @param data The main data structure containing environment variables.
 * @return EXIT_SUCC on success, EXIT_FAIL on failure.
 */
static int	expand_command(t_command *cmd_node, t_data *data)
{
	while (cmd_node)
	{
		if (cmd_node->type_quote != '\'')
		{
			if (expand_var(&cmd_node->command, data))
				return (EXIT_FAIL);
		}
		cmd_node = cmd_node->next;
	}
	return (EXIT_SUCC);
}

/**
 * @brief Expands environment variables within a list of strings (arguments or flags).
 *
 * Iterates through a linked list of strings and expands any environment variables
 * unless the string is enclosed in single quotes.
 *
 * @param list The list of strings to process.
 * @param data The main data structure containing environment variables.
 * @return EXIT_SUCC on success, EXIT_FAIL on failure.
 */
static int	expand_list_of_str(t_list *list, t_data *data)
{
	while (list)
	{
		if (list->type_quote != '\'')
		{
			if (expand_var(&list->content, data))
				return (EXIT_FAIL);
		}
		list = list->next;
	}
	return (EXIT_SUCC);
}

/**
 * @brief Expands environment variables in all commands, arguments, and flags.
 *
 * Processes all commands, arguments, and flags in the given data structure
 * to expand environment variables.
 *
 * @param data The main data structure containing commands, arguments, flags, and environment variables.
 * @return EXIT_SUCC on success, EXIT_FAIL on failure.
 */
int	expand_tokens(t_data *data)
{
	t_command	*current_cmd_node;

	current_cmd_node = data->command;
	while (current_cmd_node)
	{
		if (expand_command(current_cmd_node, data))
			return (EXIT_FAIL);
		if (expand_list_of_str(current_cmd_node->arguments, data))
			return (EXIT_FAIL);
		if (expand_list_of_str(current_cmd_node->flags, data))
			return (EXIT_FAIL);
		current_cmd_node = current_cmd_node->next;
	}
	return (EXIT_SUCC);
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
        if (expand_var(&input, &data) == EXIT_SUCC)
            printf("Expanded: %s\n\n", input);
        else
            printf("Expansion failed\n\n");
        free(input);
		i++;
	}

    return 0;
} */
