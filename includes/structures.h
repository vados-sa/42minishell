/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:14:46 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/08/03 13:08:18 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_token
{
	char			*value;
	char			*type;
	int				type_quote;
	struct s_token	*next;
}	t_token;

typedef struct s_command
{
	char				*command;
	t_list				*arguments;
	t_list				*flags;
	struct s_command	*next;
}	t_command;

typedef struct s_data
{
	char		*args; //check
	char		**env;
	char		*path;
	int			input_fd;
	char		*input_type;
	int			input_type_quote;
	char		*input_value;
	int			output_fd;
	char		*output_type;
	int			output_type_quote;
	char		*output_value;
	int			exit_status;
	t_token		*token;
	t_command	*command;
}	t_data;

#endif
