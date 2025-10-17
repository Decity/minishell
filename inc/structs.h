/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:14:03 by elie              #+#    #+#             */
/*   Updated: 2025/10/17 11:29:45 by dbakker          ###   ########.fr       */
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

typedef struct s_pwd
{
	char	*pwd;
	char	*old_pwd;
}	t_pwd;


typedef struct s_data
{
	char	*current_directory;
	char	*input;
	char	**tokens;
	t_pwd	directory;
	t_list	*envp;
	t_cmd	*command;
}	t_data;

#endif