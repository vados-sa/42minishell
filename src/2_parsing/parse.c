/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:10:50 by vados-sa          #+#    #+#             */
/*   Updated: 2024/08/07 13:10:53 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	split_token(t_data *data)
{
	t_token	*token;
	int		create_new_command;
	int		exit_s;

	token = data->token;
	create_new_command = 1;
	while (token)
	{
		exit_s = 0;
		if (token->type[0] == '<')
			exit_s = open_redir_in(data, token, O_RDONLY);
		else if (ft_strcmp(token->type, OUTPUT) == 0)
			exit_s = open_redir_out(data, token, O_WRONLY | O_TRUNC | O_CREAT);
		else if (ft_strcmp(token->type, APPEND) == 0)
			exit_s = open_redir_out(data, token, O_WRONLY | O_APPEND | O_CREAT);
		else if (ft_strcmp(token->type, OTHERS) == 0)
			exit_s = split_others_token(data, token, &create_new_command);
		else
			create_new_command = 1;
		if (exit_s)
			return (EXIT_FAIL);
		token = token->next;
	}
	return (EXIT_SUCC);
}

int	open_redir_in(t_data *data, t_token *token, int flag)
{
	if (ft_strcmp(data->input_type, STDIN) != 0 \
		&& ft_strcmp(data->input_type, HEREDOC) != 0)
		close(data->input_fd);
	data->input_value = ft_strdup(token->value);
	if (!data->input_value)
		return (perror_return_error("redirection value"));
	data->input_type = token->type;
	data->input_type_quote = token->type_quote;
	if (token->type_quote != '\'')
		expand_var(&token->value, data);
	if (ft_strcmp(data->input_type, HEREDOC) != 0)
	{
		data->input_fd = open(data->input_value, flag, 0644);
		if (data->input_fd < 0)
			return (perror_return_error(data->input_value));
	}
	return (EXIT_SUCC);
}

int	open_redir_out(t_data *data, t_token *token, int flag)
{
	if (ft_strcmp(data->output_type, STDOUT) != 0)
		close(data->output_fd);
	data->output_value = ft_strdup(token->value);
	if (!data->output_value)
		return (perror_return_error("redirection value"));
	data->output_type = token->type;
	data->output_type_quote = token->type_quote;
	if (token->type_quote != '\'')
		expand_var(&token->value, data);
	data->output_fd = open(data->output_value, flag, 0644);
	if (!data->output_fd)
		return (perror_return_error(data->output_value));
	return (EXIT_SUCC);
}

void	remove_possible_quotes(char *str)
{
	int	src_pos;
	int	dst_pos;

	src_pos = 0;
	dst_pos = 0;
	while (str[src_pos])
	{
		if (str[src_pos] != SINGLE_Q && str[src_pos] != DOUBLE_Q)
		{
			str[dst_pos] = str[src_pos];
			dst_pos++;
		}
		src_pos++;
	}
	str[dst_pos] = '\0';
}

int	split_others_token(t_data *data, t_token *token, int *create_new_command)
{
	static t_command	*command;

	if (*create_new_command)
	{
		*create_new_command = 0;
		command = create_command_node(data);
		if (!command)
			return (EXIT_FAIL);
		if (fill_node(command, token, "COMMAND"))
			return (EXIT_FAIL);
	}
	else if (token->value[0] == '-' && !ft_isspace(token->value[1]) && \
			token->value[1])
	{
		remove_possible_quotes(token->value);
		if (fill_node(command, token, "FLAG"))
			return (EXIT_FAIL);
	}
	else
	{
		remove_possible_quotes(token->value);
		if (fill_node(command, token, "ARGUMENT"))
			return (EXIT_FAIL);
	}
	return (EXIT_SUCC);
}

int	parse(t_data *data)
{
	if (split_token(data))
		return (EXIT_FAIL);
	//expand
	//handle heredoc
	return (EXIT_SUCC);
}

void print_commands(t_data data, t_command *command) {
    while (command) {
        printf("Command: %s\n", command->command);
        t_list *arg = command->arguments;
        while (arg) {
            printf("  Argument: %s\n", arg->content);
            arg = arg->next;
        }
        t_list *flag = command->flags;
        while (flag) {
            printf("  Flag: %s\n", flag->content);
            flag = flag->next;
        }
        command = command->next;
    }
	printf("INPUT FD: %i\n", data.input_fd);
	printf("INPUT VALUE: %s\n", data.input_value);
	printf("INPUT TYPE: %s\n", data.input_type);
	printf("OUTPUT FD: %i\n", data.output_fd);
	printf("OUTPUT VALUE: %s\n", data.output_value);
	printf("OUTPUT TYPE: %s\n", data.output_type);
	
}

// Function to free a linked list
void free_list(t_list *list) {
    t_list *temp;
    while (list) {
        temp = list;
        list = list->next;
        free(temp->content);
        free(temp);
    }
}

// Function to free command structures
void free_commands(t_command *command) {
    t_command *temp;
    while (command) {
        temp = command;
        command = command->next;
        free(temp->command);
        free_list(temp->arguments);
        free_list(temp->flags);
        free(temp);
    }
}

// Run test function
void run_test(char *input) {
    t_data data;
    memset(&data, 0, sizeof(t_data));  // Initialize the data structure to zero
	data.input_fd = STDIN_FILENO;
	data.input_value = NULL;
	data.input_type = STDIN;
	data.output_fd = STDOUT_FILENO;
	data.output_value = NULL;
	data.output_type = STDOUT;
	data.exit_status = 0;
    data.args = input;

    // Call the lexer and parser
    printf("Input: %s\n", input);
    fflush(stdout);
    if (lex(&data) == EXIT_SUCC) {
        if (parse(&data) == EXIT_SUCC) {
            // Print the commands
            printf("Parsing successful. Printing commands...\n");
            fflush(stdout);
            print_commands(data, data.command);
        } else {
            printf("Parsing failed.\n");
            fflush(stdout);
        }
    } else {
        printf("Lexing failed.\n");
        fflush(stdout);
    }

    // Free the allocated commands
    free_commands(data.command);
    printf("Commands freed.\n");
    fflush(stdout);
}

int main() {
    printf("Test 1: Basic Command Without Arguments\n");
    run_test("ls -la");

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
    run_test("cat < Makefile > output.txt");

    printf("\nTest 8\n");
    run_test("ls | grep \"search\" > \"output.txt\"");

    printf("\nTest 9\n");
    run_test("echo \"Hello World\" > \"my file.txt\"");

    printf("\nTest 10\n");
    run_test("echo 'Single quotes with \"double quotes\" inside'");

    printf("\nTest 11\n");
    run_test("echo \"Double quotes with 'single quotes' inside\"");

    printf("\nTest 12\n");
    run_test("cat < \"Makefile\" | grep \"search_term\" > \"output file.txt\"");

    printf("\nTest 13\n");
    run_test("grep \"term\" < \"Makefile\" | sort | uniq > \"output file.txt\"");

    printf("\nTest 14\n");
    run_test("< \"Makefile\" cat");

    printf("\nTest 15\n");
    run_test("echo \"This is a \"quoted\" word\" > \"output file.txt\"");

    printf("\nTest 16\n");
    run_test("ls -la /home/user");

    printf("\nTest 17\n");
    run_test("ls \"-la\"");

    printf("\nTest 18\n");
    run_test("ls \"-l\"a");

    printf("\nTest 19\n");
    run_test("ls -l\"a\"");

    printf("\nTest 20\n");
    run_test("ls -\"l\"a");

    printf("\nTest 21\n");
    run_test("find . -name \"*.c\" -print");

    printf("\nTest 22\n");
    run_test("echo \"Hello World\" > \"my file.txt\"");

    printf("\nTest 23\n");
    run_test("cat <<-END | wc -l");

	printf("\nTest 24\n");
    run_test("echo - \"\" \"  \" hello");

	printf("\nTest 25\n");
    run_test("echo \"Hello\" > file1.txt > file2.txt");

    return 0;
}
