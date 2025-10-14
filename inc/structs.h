/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:14:03 by elie              #+#    #+#             */
/*   Updated: 2025/10/14 15:33:42 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_redirection	s_redirection;
typedef struct s_commands		t_cmd;
typedef struct s_data			t_data;

typedef struct s_redirection
{
	int		redirection_type;
	int		input_fd;
	int		output_fd;
	char	*input_file_name;
	char	*output_file_name;
}	s_redirection;

typedef struct s_commands
{
	char			**arguments;
	s_redirection	redirection;
	t_cmd		*next;
}	t_cmd;

typedef struct s_data
{
	char	**envp;
	char	*current_directory;
	char	*input;
	char	**tokens;
	t_cmd *command;
}	t_data;

#endif