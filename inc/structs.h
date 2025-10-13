/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:14:03 by elie              #+#    #+#             */
/*   Updated: 2025/10/13 22:50:17 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_commands
{
	char	**arguments;
	char	*redirection;
	char	*input;
	char	*output;
}	t_commands;

typedef struct s_data
{
	char		*current_directory;
	char		*input;
	char		**tokens;
	t_list		*envp;
	t_commands	*command;
}	t_data;

#endif