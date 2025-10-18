/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:08:30 by ebelle            #+#    #+#             */
/*   Updated: 2025/10/18 12:55:09 by elie             ###   ########.fr       */
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
void	set_commands(t_data *data);
void	apply_shell_expansions(t_data *data);
void	set_redirections(t_data *data);
void	execute(t_data *data);

// Parsing
bool	is_redirection(char *str);
t_cmd	*init_command(void);
void	assign_redirection(char **tokens, t_cmd *cmd);


// Tokenization
void	tokenize(t_data *data, int token_count);
int 	set_tokens(t_data *data);
bool	is_quote(int c);
int		count_tokens(char *input);

char	*normalize_whitespace(const char *str);
size_t	get_normalized_str_len(const char *str);
uint8_t	get_token_type(const char *str);
uint8_t	get_redirection_type(const char *str);
uint8_t	get_quote_type(const char *str);
bool	has_redirection_target(char *str);
int		validate_token_str(char *str);
bool	validate_quotation(char *str);


// Shell expansion utilities
char	*get_parameter_name(const char *str);
char	*get_parameter_var(const char *str);

size_t	expand_single_variable(char **str, size_t index);
void	expand_tilde(char **str);
void	expand_env_variables(char **str);

void	remove_quotation(char **str);

// Cleanup
void	cleanup_data(t_data *data);
void	cleanup_commands(t_cmd **cmd);

// Debug
void	debug(t_data *data);

// Built-ins
void	env_print(const t_list *envp);
void	env_single_print(const t_list *envp);
void	env_all_print(const t_list *envp);
void	unset_env(t_list **head, const char *name);
size_t	env_namelen(const char *name);
void	*export_env(t_list *list, const char *envvar);

#endif
