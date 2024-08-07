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