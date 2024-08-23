/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:10:50 by vados-sa          #+#    #+#             */
/*   Updated: 2024/08/23 15:51:51 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern char** environ; //remember to take this off

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
			return (EXIT_FAILURE);
		token = token->next;
	}
	return (EXIT_SUCCESS);
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
	return (EXIT_SUCCESS);
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
	return (EXIT_SUCCESS);
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

int	split_others_token(t_data *data, t_token *token, int *add_new_cmd)
{
	static t_command	*command;

	if (*add_new_cmd)
	{
		*add_new_cmd = 0;
		command = create_command_node(data);
		if (!command)
			return (EXIT_FAILURE);
		if (fill_node(command, token, "COMMAND"))
			return (EXIT_FAILURE);
	}
	else if (token->value[0] == '-' && !ft_isspace(token->value[1]) && \
			token->value[1])
	{
		remove_possible_quotes(token->value);
		if (fill_node(command, token, "FLAG"))
			return (EXIT_FAILURE);
	}
	else
	{
		// remove_possible_quotes(token->value); // cannot be here -> CHECK WHEN TO REMOVE
		if (fill_node(command, token, "ARGUMENT"))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	parse(t_data *data)
{
	if (split_token(data))
		return (EXIT_FAILURE);
	if (expand_tokens(data))
		return (EXIT_FAILURE);
	if (organize_final_cmd_array(data))
		return (EXIT_FAILURE);
	if (ft_strcmp(data->input_type, HEREDOC) == 0)
	{
		if (handle_heredoc(data))
			return (EXIT_FAIL);
	}
	return (EXIT_SUCCESS);
}

/* void print_commands(t_data data, t_command *command) {
    while (command) {
        printf("Command: %s\n", command->command);
        t_list *arg = command->arguments;
        while (arg) {
            printf("  Argument: %s\n", arg->content);
			//printf("quote type: %d\n", arg->type_quote);
            arg = arg->next;
        }
        t_list *flag = command->flags;
        while (flag) {
            printf("  Flag: %s\n", flag->content);
            flag = flag->next;
        }
		int	i = 0;
		printf("  Final command array:\n");
		while (command->final_av[i])
		{
			printf("av[%d] - %s\n", i, command->final_av[i]);
			i++;
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
	data.env = environ;

    // Call the lexer and parser
    printf("Input: %s\n", input);
    fflush(stdout);
    if (lex(&data) == EXIT_SUCCESS) {
        if (parse(&data) == EXIT_SUCCESS) {
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
    //printf("Commands freed.\n");
    fflush(stdout);
}

int main()
{
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
    run_test("echo    \"Hello  \'   World\"    >   \"my file.txt\"");

    printf("\nTest 23\n");
    run_test("cat <<-END | wc -l");

	printf("\nTest 24\n");
    run_test("echo - \"\" \"  \" hello");

	printf("\nTest 25\n");
    run_test("echo \"Hello\" > file1.txt > file2.txt");

	printf("\nTest 26\n");
    run_test("echo \"Hello\" | > out");

	printf("\nExport Test 01\n");
    run_test("export VAR=value");

	printf("\nExport Test 02\n");
    run_test("export VAR=\"value with spaces\"");

	printf("\nExport Test 03\n");
    run_test("export VAR=\'single quoted value\'");
 
	printf("\nExport Test 04\n");
    run_test("export PATH=\'$PATH:/new/path\'");
	
	printf("\nExport Test 05\n");
    run_test("export HELLO MY_VAR=This\" is ${USER}'s home\"");

	printf("\nExport Test 06\n");
    run_test("export VAR=\"hello\"\" vanessa\"santos VAR1=\"hello\"\"malu\"rabelo");
	
	printf("\nTest 07\n");
    run_test("export WRONG_VAR=vanessa dos santos");

	printf("\nExport Test 08\n");
    run_test("export \"VAR=value=isso=aquilo\"");

	printf("\nExport Test 09\n");
    run_test("export \"VAR=hello\"myname\"is \"vanessa");

    return 0;
} */
