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
	//printf("%c\n", arg[i]);
	while (ft_isspace(arg[i]))
		i++;
	//printf("%c\n", arg[i]);
	if (arg[i] == SINGLE_Q || arg[i] == DOUBLE_Q)
	{
		type_quote = arg[i];
		i++;
	}
	//printf("%c\n", arg[i]);
	start = i;
	while (arg[i] && ((type_quote == SINGLE_Q || type_quote == DOUBLE_Q) \
		|| !ft_isspace(arg[i])) && !ft_strchr("<|>", arg[i])
		&& !((type_quote == SINGLE_Q && arg[i] == SINGLE_Q) \
		|| (type_quote == DOUBLE_Q && arg[i] == DOUBLE_Q)))
		i++;
	//printf("%c\n", arg[i]);
	*token = create_token(i - start, &arg[start], type, type_quote);
	if (type_quote)
		i++;
	return (i);
}
int	check_double_operator(char *arg)
{
	if (!look_for_operator(*(arg + 1)))
		return (EXIT_SUCC);
	else
	{
		if ((*arg == '<' && *(arg + 1) == '<')
			|| (*arg == '>' && *(arg + 1) == '>'))
			return (EXIT_SUCC);
		else
		{
			return (print_error_code(OPER_STX_ERROR, *(arg + 1), EXIT_FAIL));
		}
	}
}

void	create_token_list(t_data*data, t_token*new)
{
	t_token	*last;

	last = ft_lst_last_mod(data->token);
	if (!last)
	{
		data->token = new;
		return ;
	}
	last->next = new;
}

t_token	*ft_lst_last_mod(t_token*lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	print_error_code(char *message, char tkn, int exit_code)
{
	printf("%s'%c'\n", message, tkn);
	return (exit_code);
}

int	handle_operator(t_data *data, char *arg, int pos)
{
	int		i;
	t_token	*token;

	i = pos;
	if (check_double_operator(&arg[pos]))
		return (-1);
	if ((arg[pos] == '<' || arg[pos] == '>'))
		i += handle_redirection(&arg[pos], &token);
	if (arg[pos] == '|')
	{
		token = create_token(0, &arg[pos], PIPE, 0); // type quote NULL or NONE?
		i++;
	}
	if (!token)
		return (-1); //check if it's correct
	create_token_list(data, token);
	return (i);
}

int	look_for_operator(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

void test_handle_operator(char *arg) {
    t_data data;
    memset(&data, 0, sizeof(data));

    printf("Testing handle_operator with input: '%s'\n", arg);

    int pos = 0;
    while (arg[pos]) {
        if (look_for_operator(arg[pos])) {
			printf("%c\n", arg[pos]);
            int len = handle_operator(&data, arg, pos);
            if (len == -1) {
                //printf("Failed to handle operator at position %d\n", pos);
                break;
            }
            pos = len;
        } else {
            pos++;
        }
    }

    // Print the tokens
    t_token *token = data.token;
    while (token) {
        printf("Token value: %s, type: %s, quote: %d\n",
               token->value, token->type, token->type_quote);
        t_token *next = token->next;
        free(token->value);
        free(token);
        token = next;
    }
    printf("\n");
}

int main() {
    test_handle_operator("cat < input | grep cat > output");
    test_handle_operator("<< 'example text' >> \"another example\" > no quotes < input");
    test_handle_operator("ls -l | grep '^d' > directories");
    test_handle_operator("echo \"Hello World\" | wc -l");

    return 0;
}
