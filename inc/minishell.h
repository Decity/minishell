/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:08:30 by ebelle            #+#    #+#             */
/*   Updated: 2025/10/13 22:58:38 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// headers
# include "../lib/libft/inc/libft.h"
# include "../lib/libft/inc/ft_printf.h"
# include "../lib/libft/inc/get_next_line.h"
# include "structs.h"
# include "definitions.h"

// standard libs
# include <stdio.h>
# include <readline/readline.h>
# include <stdlib.h>

// Shell operations
void	set_tokens(t_data *data);
void	set_commands(t_data *data);
void	apply_shell_expansions(t_data *data);
void	set_redirections(t_data *data);
void	execute(t_data *data);


// Tokenization
void	tokenize(t_data *data, int token_count);
void	set_tokens(t_data *data);
bool	is_quote(int c);
int		count_tokens(char *input);


// Shell expansion utilities
char	*get_parameter_name(const char *str);
char	*get_parameter_var(const char *str);

size_t	expand_single_variable(char **str, size_t index);
void	expand_tilde(char **str);
void	expand_env_variables(char **str);

void	remove_quotation(char **str);

// Cleanup
void	cleanup_data(t_data *data);

// Debug
void	debug(t_data *data);

// Built-ins
t_list	*envp_to_llist(const char **envp);
void	env_print(const t_list *envp);

#endif
