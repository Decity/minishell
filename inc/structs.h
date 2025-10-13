/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:14:03 by elie              #+#    #+#             */
/*   Updated: 2025/10/13 08:29:43 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_cmds	t_cmds;

typedef struct s_parse
{
	char	**arguments;
	char	*redirection;
	char	*input;
	char	*output;
}	t_parse;

typedef struct s_cmds
{
	t_parse	*content;
	t_cmds	*next;
	t_cmds	*prev;
}	t_cmds;

typedef struct s_data
{
	char	**envp;
	char	*current_directory;
	char	*input;
	char	**tokens;
	t_cmds	*command;
}	t_data;

#endif