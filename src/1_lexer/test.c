#include "../../includes/minishell.h"
#include <stdio.h>

#define PIPE_SINTAX_ERROR "syntax error near unexpected token "
#define QUOTE_SINTAX_ERROR "syntax error: unclosed quote "
#define OPER_SINTAX_ERROR "syntax error near unexpected token"

/* int	check_end_of_string(char *str)
{
	if ((*str == '<' || *str == '>') && *str == *(str + 1) && !*(str + 2))
	{
		printf("token expected after symbol '%c%c'\n", *str, *str);
		return (EXIT_FAILURE);
	}
	if (!*(str + 1))
	{
		printf("token expected after symbol '%c'\n", *str);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
} */

int	unclosed_quotes(char *input)
{
	int	i;
	int	sing_quote_open;
	int	doub_quote_open;

	i = -1;
	sing_quote_open = 0;
	doub_quote_open = 0;
	while (input[++i])
	{
		if (input[i] == '\'' && !doub_quote_open)
			sing_quote_open = !sing_quote_open;
		else if (input[i] == '\"' && !sing_quote_open)
			doub_quote_open = !doub_quote_open;
	}
	return (sing_quote_open || doub_quote_open);
}

int	ft_isspace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

size_t	ft_strlen(const char*s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	look_for_operator(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int print_error_code(char *message, char tkn, int exit_code)
{
	printf("%s'%c'\n", message, tkn);
	return (exit_code);
}

int	check_end_of_string(char *cpy_arg)
{
	int	i;
	int len;

	i = 0;
	while (ft_isspace(cpy_arg[i]))
	{
		if (!cpy_arg[i + 1])
			return (EXIT_FAILURE);
		i++;
	}
	if (cpy_arg[i] == '|')
		return (print_error_code(PIPE_SINTAX_ERROR, cpy_arg[i], EXIT_FAILURE));
	if (unclosed_quotes(cpy_arg))
		return (print_error_code(QUOTE_SINTAX_ERROR, cpy_arg[i], EXIT_FAILURE));
	len = ft_strlen(cpy_arg);
	while (len > 0 && ft_isspace(cpy_arg[len - 1]))
		len--;
	if (look_for_operator(cpy_arg[len -1]))
		return (print_error_code(OPER_SINTAX_ERROR, cpy_arg[len - 1], EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

int main(void) {
    char *test_cases[] = {
        "<    ",
        ">    ",
        ">>",
        "<<",
        "<>",
        "><",
        "< ",
        "> | echo", // should be an error
        "<< more text",
        ">> more text",
		"<> more text",
        ">< more text",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        printf("Testing: \"%s\"\n", test_cases[i]);
        int result = check_end_of_string(test_cases[i]);
        if (result == EXIT_SUCCESS) {
            printf("No error detected.\n");
        }
        printf("\n");
    }

    return 0;
}