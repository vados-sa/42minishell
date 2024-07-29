#include "../../includes/minishell.h"


size_t	ft_strlcpy(char*dest, const char*src, size_t n)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(src);
	i = 0;
	if (n != 0)
	{
		while (src[i] != '\0' && i < (n - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (len);
}

size_t	ft_strlen(const char*s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char*s, int c)
{
	int		i;
	char	temp_c;
	char	*temp_s;

	i = 0;
	temp_c = (char)c;
	temp_s = (char *)s;
	while (temp_s[i] != '\0')
	{
		if (temp_s[i] == temp_c)
			return (temp_s + i);
		i++;
	}
	if (temp_s[i] == '\0' && temp_c == '\0')
		return (temp_s + i);
	return (0);
}

t_token	*create_token(int size_lengh, char *str, char *type, int type_quote)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		perror("failed to allocate memory");
		return (NULL);
	}
	if (size_lengh > 0)
	{
		token->value = malloc((size_lengh + 1) * sizeof(char));
		if (!token->value)
		{
			perror("failed to allocate memory"); 
			return (NULL);
		}
		ft_strlcpy(token->value, str, size_lengh + 1);
	}
	else
		token->value = NULL;
	token->type = type;
	token->type_quote = type_quote;
	token->next = NULL;
	return (token);
}

int	ft_isspace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	assign_type_redirection(char *arg, char **type)
{
	int	i;

	i = 0;
	if (arg[i] == arg[i + 1])
	{
		if (arg[i] == '<')
			*type = HEREDOC;
		else
			*type = APPEND;
		i += 2;
		return (i);
	}
	else
	{
		if (arg[i] == '<')
			*type = INPUT;
		else
			*type = OUTPUT;
		i += 1;
		return (i);
	}
}

int	handle_redirection(char *arg, t_token **token)
{
	char	*type;
	int		type_quote;
	int		i;
	int		start;

	type_quote = 0;
	i = assign_type_redirection(arg, &type);
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == SINGLE_Q || arg[i] == DOUBLE_Q)
	{
		type_quote = arg[i];
		i++;
	}
	start = i;
	while (arg[i] && ((type_quote == SINGLE_Q || type_quote == DOUBLE_Q) \
		|| !ft_isspace(arg[i])) && !ft_strchr("<|>", arg[i])
		&& !((type_quote == SINGLE_Q && arg[i] == SINGLE_Q) \
		|| (type_quote == DOUBLE_Q && arg[i] == DOUBLE_Q)))
		i++;
	*token = create_token(i - start, &arg[start], type, type_quote);
	if (type_quote)
		i++;
	return (i);
}

void test_handle_redirection(char *arg) {
    t_token *token = NULL;
    int len = handle_redirection(arg, &token);

    if (token) {
        printf("Input: %s\n", arg);
        printf("Token type: %s\n", token->type);
        printf("Token quote: %d\n", token->type_quote ? token->type_quote : 0);
        printf("Token value: %s\n", token->value);
        printf("Processed length: %d\n", len);
		printf("Position in string: %c and next %c\n", arg[len], arg[len+1]);

        free(token->value);
        free(token);
    } else {
        printf("Input: %s\n", arg);
        printf("No token created.\n");
    }
    printf("\n");
}

int main() {
    test_handle_redirection("<<      'example_text.txt'xy");
    test_handle_redirection(">>     \"another example\"xy");
    test_handle_redirection(">         no quotes");
    test_handle_redirection("< input x");

    return 0;
}
