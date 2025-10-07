/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:08:30 by ebelle            #+#    #+#             */
/*   Updated: 2025/10/07 17:24:28 by elie             ###   ########.fr       */
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

// Shell operations
void	set_tokens(t_data *data);
void	set_commands(t_data *data);
void	set_shell_expansions(t_data *data);
void	set_redirections(t_data *data);
void	execute(t_data *data);


// Tokenization
void	tokenize(t_data *data, int token_count);
void	set_tokens(t_data *data);
bool	is_quote(int c);
int		count_tokens(char *input);

// Shell expansion utilities
bool	is_valid_parameter(const char *str);
char	*get_parameter_name(const char *str);
char	*get_parameter_var(const char *str);
size_t	do_the_actual_expansion(char **str);
void	expand_tilde(char **str);
void	expand_env_parameter(char **str);
void	remove_quotation(char **str);

// TEMP, MOVE TO LIBFT
char	*ft_strreplace(const char *base_str, const char *pattern, const char *replacement);
void	ft_repoint(char **old_str, char *new_str);
size_t	ft_count_occurrences(const char *base_str, const char *pattern);

// Cleanup
void	cleanup_data(t_data *data);

// Debug
void	debug(t_data *data);

#endif
