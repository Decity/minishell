/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:08:30 by ebelle            #+#    #+#             */
/*   Updated: 2025/10/01 17:06:27 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// headers
# include "../lib/libft/inc/libft.h"
# include "structs.h"
# include "definitions.h"

// standard libs
# include <stdio.h>
# include <readline/readline.h>
# include <stdlib.h>


void	set_tokens(t_data *data);
void	set_commands(t_data *data);
void	set_shell_expansions(t_data *data);
void	set_redirections(t_data *data);
void	execute(t_data *data);


// Cleanup
void	cleanup_data(t_data *data);

// Debug
void	debug(t_data *data);

#endif
