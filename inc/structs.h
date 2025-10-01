/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:14:03 by elie              #+#    #+#             */
/*   Updated: 2025/10/01 17:12:08 by elie             ###   ########.fr       */
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
	char	*current_directory;
	char	*input;
	char	**tokens;
	t_commands *command;
}	t_data;

#endif