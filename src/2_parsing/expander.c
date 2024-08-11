/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:29:30 by vados-sa          #+#    #+#             */
/*   Updated: 2024/08/11 16:06:22 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_var_len(char *str)
{
	int	i;
	int	len;

	i = 1;
	len = 0;
	if (str[1] == '?')
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		len++;
		i++;	
	}
	return (len);
}

char	*get_exp_env(char *str, int len, char **env_arg)
{
	while(*env_arg)
	{
		if (!ft_strncmp(str + 1, *env_arg, len)
			&& (*env_arg)[len] == '=')
			return(*env_arg + len + 1);
		env_arg++;
	}
	return("");
}

char	*ft_concat(char *s1, char *s2, char *s3)
{
	char *temp;
	char *result;

	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, s3);
	free (temp);
	if (!result)
		return (NULL);
	return (result);
}

void	free_str_pieces(char **s1, char **s2, char **s3)
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
	after_var = ft_substr(*str, *i + len + 1, ft_strlen(*str) - len - *i);
	if ((*str)[*i + 1] == '?')
		exp_var = ft_itoa(data->exit_status);
	else
		exp_var = ft_strdup(get_exp_env(&(*str)[*i], len, data->env));
	*i += ft_strlen(exp_var) + 1; //check if +1 is not giving any issues
	exp_str = ft_concat(before_var, exp_var, after_var);
	free_str_pieces(&before_var, &exp_var, &after_var);
	if (!exp_str)
		return (NULL);
	return(exp_str);
}
// SAVE ABOVE FUNCTIONS INTO EXPANDER_UTILS.C

int	expand_var(char **str, t_data *data)
{
	int		i;
	char 	*temp;
	
	i = 0;
	temp = NULL;
	while((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			temp = concat_expanded_var(str, &i, data);
			printf ("%s\n", temp);
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

int	expand_command(t_command *cmd_node, t_data *data)
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

int	expand_list_of_str(t_list *list, t_data *data)
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
		if (expand_lisd_of_str(current_cmd_node->flags, data))
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
        "$USER is the current user",
        "The shell is $SHELL",
        "Path is set to $PATH",
        "Exit status was $?",
        "Unknown variable $UNKNOWN",
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