/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:09:51 by vados-sa          #+#    #+#             */
/*   Updated: 2024/07/28 11:26:04 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	tokenize(t_data *data, char *cpy_arg)
{
	int	i;
	int	j;

	i = 0;
	while (cpy_arg[i])
	{
		j = i;
		if (ft_isspace(cpy_arg[i]))
			i++;
		else if (look_for_operator(cpy_arg[i]))
			i += handle_operator(data, &cpy_arg[i]);
		else if (look_for_quotes(cpy_arg[i]))
			i += handle_quotes(data, &cpy_arg[i]);
		else
			i += handle_word(data, &cpy_arg[i]);
		if (i < j)
			return (EXIT_FAIL);
	}
	return (EXIT_SUCC);
}

int	lex(t_data *data)
{
	char	*cpy_arg;
	int		i;

	i = 0;
	cpy_arg = data->args;
	if (check_input(cpy_arg))
		return (EXIT_FAIL);
	if (tokenize(data, cpy_arg))
		return (EXIT_FAIL);
	return (EXIT_SUCC);
}

/* void free_tokens(t_token *token) {
    t_token *temp;
    while (token) {
        temp = token;
        token = token->next;
        free(temp->value);
        free(temp);
    }
}

void print_tokens(t_token  *token) {
    while (token) {
        printf("Value: %s, Type: %s, Quote Type: %d\n", token->value, token->type, token->type_quote);
        token = token->next;
    }
}

void run_test(char *input) {
    t_data data;
    memset(&data, 0, sizeof(t_data));  // Initialize the data structure to zero
    data.args = input;

    // Call the lexer
    printf("Input: %s\n", input);
    fflush(stdout);
    if (lex(&data) == EXIT_SUCC) {
        // Print the tokens
        printf("Lexing successful. Printing tokens...\n");
        fflush(stdout);
        print_tokens(data.token);
    } else {
        printf("Lexing failed.\n");
        fflush(stdout);
    }

    // Free the allocated tokens
    free_tokens(data.token);
    printf("Tokens freed.\n");
    fflush(stdout);
}

int main() {
    printf("Test 1: Basic Command Without Arguments\n");
    run_test("ls");

    printf("\nTest 2: Basic Command With Arguments\n");
    run_test("echo Hello World");

    printf("\nTest 3: Command With Redirection\n");
    run_test("echo Hello > output.txt");

    printf("\nTest 4: Command With Quotes\n");
    run_test("echo \"Hello World\"");

    printf("\nTest 5: Command With Single Quotes\n");
    run_test("echo 'Hello World'");

    printf("\nTest 6: Command With Pipe\n");
    run_test("cat file.txt | grep Hello");

    printf("\nTest 7: Command With Multiple Redirections\n");
    run_test("cat < input.txt > output.txt");

    return 0;
}


 */