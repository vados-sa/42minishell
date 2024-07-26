/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:14:46 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/07/26 14:36:00 by mrabelo-         ###   ########.fr       */
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
	char				*name;
	char				**args;
	struct s_command	*next;
}	t_command;

typedef struct s_data
{
	char		*args; //check
	char		**env;
	char		*path;
	int			input;
	int			output;
	int			exit_status;
	t_token		*token;
	t_command	*command;
}	t_data;

#endif
