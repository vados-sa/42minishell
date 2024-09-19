/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:10:58 by vados-sa          #+#    #+#             */
/*   Updated: 2024/09/18 17:12:23 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec(t_data*data)
{
	int		qt_cmd;
	int		**fds;
	pid_t	*id_p;

	qt_cmd = ft_lstsize_mod(data->command);
	fds = create_pipes(qt_cmd);
	if (!fds)
		return (EXIT_FAIL);
	id_p = (pid_t *)ft_calloc((qt_cmd), sizeof(pid_t));
	if (!id_p)
		return (EXIT_FAIL);
	processing(fds, id_p, data);
	free_double_pointer_int(fds, qt_cmd);
	free(id_p);
	return (EXIT_SUCC);
}

static void	close_all_pipes(int **fds, int cmds_num)
{
	int	i;

	i = 0;
	while (i < cmds_num - 1)
	{
		close_fd(&fds[i][0]);
		close_fd(&fds[i][1]);
		i++;
	}
}
//code that chatgpt provided 
void child_exec(pid_t *id_p, int pos, t_data *data, int **fds)
{
	int i;
	int exit_code;

	if (!id_p || pos <= 0 || !data || !fds)
	    return ;
	i = 0;
	while (i < pos)
	{
		if (id_p[i] > 0)
		{
	    	waitpid(id_p[i], &exit_code, 0);
	    	if (i == pos - 1)
			{
	    		if (WIFEXITED(exit_code))
	    			data->exit_status = WEXITSTATUS(exit_code);
	    		else if (WIFSIGNALED(exit_code))
	    			data->exit_status = WTERMSIG(exit_code) + 128;
	    		else
	    			data->exit_status = -1;
			}
		}
		i++;
	}
}


/* void	child_exec(pid_t *id_p, int pos, t_data *data, int **fds)
{
	int	i;
	int	exit_code;

	if (!id_p || pos <= 0 || !data || !fds)
		return ;
	i = 0;
	while (i < pos)
	{
		if (id_p[i] > 0)
		{
			waitpid(id_p[i], &exit_code, 0);
			if (i == pos - 1)
			{
				if (WIFEXITED(exit_code))
					data->exit_status = WEXITSTATUS(exit_code);
				else if (WIFSIGNALED(exit_code))
					data->exit_status = WTERMSIG(exit_code) + 128;
				else
					data->exit_status = -1;
			}
		}
		i++;
	}
	close_all_pipes(fds, pos);
} */

static int	process_commands(int **fds, pid_t *id_p, t_data *data)
{
	t_command	*command;
	int			i;

	command = data->command;
	i = 0;
	while (command)
	{
		if (check_if_builtin(command))
		{
			if (process_builtin(fds, i, command, data))
				return (EXIT_FAIL);
		}
		else
		{
			if (process_not_builtin(fds, i, &id_p[i], data))
				return (EXIT_FAIL);
		}
		i++;
		command = command->next;
	}
	return (EXIT_SUCC);
}

int	processing(int **fds, pid_t *id_p, t_data *data)
{
	int	cmds_num;

	if (!fds || !id_p || !data)
		return (EXIT_FAIL);
	cmds_num = ft_lstsize_mod(data->command);
	if (process_commands(fds, id_p, data) == EXIT_FAIL)
		return (EXIT_FAIL);
	close_all_pipes(fds, cmds_num);
	child_exec(id_p, cmds_num, data, fds);
	return (EXIT_SUCC);
}


/* int	processing(int **fds, pid_t *id_p, t_data *data)
{
	t_command	*command;
	int			i;

	if (!fds || !id_p || !data)
		return (EXIT_FAIL); //check necessity
	command = data->command;
	i = 0;
	while (command)
	{
		if (check_if_builtin(command))
		{
			if (process_builtin(fds, i, command, data))
				return (EXIT_FAIL);
		}
		else
		{
			if (process_not_builtin(fds, i, &id_p[i], data))
				return (EXIT_FAIL);
		}
		i++;
		command = command->next;
	}
	child_exec(id_p, i, data, fds);
	return (EXIT_SUCC);
} */

/*t_command	*create_command(char *cmd, char **args)
{
	t_command	*new_cmd;

	new_cmd = (t_command *)malloc(sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	new_cmd->command = cmd;
	new_cmd->final_av = args;
	new_cmd->next = NULL;
	return (new_cmd);
}

void	add_command(t_data *data, t_command *new_cmd)
{
	t_command	*temp;

	if (!data->command)
		data->command = new_cmd;
	else
	{
		temp = data->command;
		while (temp->next)
			temp = temp->next;
		temp->next = new_cmd;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*args2[] = {"cat", "World", NULL};
	char	*args3[] = {"wc", "-l", NULL};

	(void)argc;
	(void)argv;

	data.command = NULL;
	data.env = envp;
	data.input_fd = STDIN_FILENO;
	data.output_fd = STDOUT_FILENO;

	// Create and add commands to the linked list
	add_command(&data, create_command("cat", args2));
	add_command(&data, create_command("wc", args3));

	// Execute the pipeline
	if (exec(&data) == EXIT_FAIL)
	{
		perror("Execution failed");
		return (EXIT_FAIL);
	}

	return (EXIT_SUCC);
}*/
