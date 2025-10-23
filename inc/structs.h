/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:14:03 by elie              #+#    #+#             */
/*   Updated: 2025/10/23 15:46:15 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_redirection	t_redirection;
typedef struct s_commands		t_cmd;
typedef struct s_data			t_data;

typedef struct s_redirection
{
	int		redirection_type;
	int		input_fd;
	int		output_fd;
	char	**infile;
	char	**outfile;
}	t_redirection;

typedef struct s_commands
{
	char			**arguments;
	t_redirection	redirection;
	t_cmd			*next;
}	t_cmd;

typedef struct s_data
{
	char	*current_directory;
	char	*input;
	char	**tokens;
	t_list	*envp;
	t_cmd	*command;
}	t_data;

#endif
