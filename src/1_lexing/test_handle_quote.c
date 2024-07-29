#include "../../includes/minishell.h"

size_t	ft_strlen(const char*s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

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

t_token	*ft_lst_last_mod(t_token*lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
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

int	handle_quotes(t_data *data, char *arg, int pos)
{
	char	*end_quote;
	int		i;
	t_token	*token;

	i = pos + 1;
	end_quote = arg;
	while (end_quote[i + 1] != arg[pos])
		i++;
	if (arg[pos] == '\"')
		token = create_token(i - pos, &arg[pos + 1], OTHERS, SINGLE_Q);// check if it's correct
	else
		token = create_token(i - pos, &arg[pos + 1], OTHERS, DOUBLE_Q);// check if it's correct
	if (!token)
		return (-1); //check if it's correct
	create_token_list(data, token);
	return (i - pos + 2);
}

void test_handle_quotes(char *arg) {
    t_data data;
    data.token = NULL;
    int pos = 0;  // Adjust as needed to test specific positions within the string

    int len = handle_quotes(&data, arg, pos);

    if (data.token) {
        printf("Input: %s\n", arg);
        printf("Token type: %s\n", data.token->type);
        printf("Token quote: %d\n", data.token->type_quote ? data.token->type_quote : 0);
        printf("Token value: %s\n", data.token->value);
        printf("Processed length: %d\n", len);
		printf("%c\n", arg[len]);
        
        // Free allocated memory
        t_token *token = data.token;
        while (token) {
            t_token *temp = token;
            token = token->next;
            free(temp->value);
            free(temp);
        }
    } else {
        printf("Input: %s\n", arg);
        printf("No token created.\n");
    }
    printf("\n");
}

int main() {
    test_handle_quotes("\"example text\"x");
    test_handle_quotes("'another example'x");
    return 0;
}

