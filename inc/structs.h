/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:14:03 by elie              #+#    #+#             */
/*   Updated: 2025/11/18 14:43:39 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_rdr	t_rdr;
typedef struct s_cmd	t_cmd;
typedef struct s_data	t_data;

typedef struct s_redir
{
	int		redir_type;
	int		fd;
	char	*delimiter;
	char	*file;
}	t_redir;

typedef struct s_rdr
{
	int		input_fd;
	int		output_fd;
	t_redir	*infile;
	t_redir	*outfile;
}	t_rdr;

typedef struct s_cmd
{
	char	**args;
	t_rdr	redirect;
	t_cmd	*next;
}	t_cmd;

typedef struct s_pwd
{
	char	*pwd;
	char	*old_pwd;
}	t_pwd;

typedef struct s_data
{
	char	*input;
	char	**tokens;
	t_pwd	directory;
	t_list	*envp;
	t_cmd	*command;
	int		exit_status;
	bool	is_interactive;
}	t_data;

#endif
