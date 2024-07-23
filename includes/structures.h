/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanessasantos <vanessasantos@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:14:46 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/07/23 11:23:04 by vanessasant      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_token
{
	char	*type;
	char	*value;
}	t_token;

typedef struct s_command
{
	char				*name;
	char				**args;
	struct s_command	*next;
}	t_command;

typedef struct s_data
{
	char		*args;
	char		**envp;
	int			input;
	int			output;
	t_token		token;
	t_command	*command;
}	t_data;

#endif
