/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:08:30 by ebelle            #+#    #+#             */
/*   Updated: 2025/11/27 17:17:12 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L

// headers
# include "../lib/libft/inc/libft.h"
# include "../lib/libft/inc/ft_printf.h"
# include "../lib/libft/inc/get_next_line.h"
# include "structs.h"
# include "definitions.h"

// standard libs
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>

// Initialization
void	init(t_data *data);
uint8_t	set_input(t_data *data);

// Shell operations
void	set_commands(t_data *data);
void	apply_shell_expansions(t_data *data);
void	set_redirections(t_data *data);

// Parsing
bool	is_redirection(char *str);

/// TOKENIZATION

// tokenization.c
void	tokenize(t_data *data, size_t token_count);
size_t	set_tokens(t_data *data);
size_t	count_tokens(char *input);

// tokenization_utils.c

char	get_quote(const char c);
uint8_t	get_quote_type(const char *str);
uint8_t	get_token_type(const char *str);
uint8_t	get_redirection_type(const char *str);

// tokenization_normalization.c
char	*normalize_whitespace(const char *str);
size_t	get_normalized_str_len(const char *str);

// tokenization_validation.c
bool	validate_token_str(char *str);
bool	has_redirection_target(char *str);
bool	validate_quotation(char *str);


// Shell expansion utilities
char	*get_parameter_name(const char *str);
char	*get_parameter_var(const char *str);

size_t	expand_single_variable(char **str, size_t index);
void	expand_tilde(char **str);
void	expand_env_variables(char **str);

void	remove_quotation(char **str);

/// EXECUTION

char	*get_executable_path(const char *exec, const t_list *envp);
size_t	get_cmds_count(t_cmd *commands);
void	execution(t_data *data);
void	execute_cmds(t_data *data);
void	execute_single_cmd(t_cmd *cmd, t_data *data);
void	execute_single_builtin(t_cmd *cmd, t_data *data);
void	execute_pipeline_child(t_cmd *cmd, t_data *data, int *pipefd, int prev_pipefd, bool is_first, bool is_last);
void	wait_for_children(pid_t *pids, size_t count, t_data *data);
void	execute_binary(t_cmd *cmd, t_list *envp);
bool	is_builtin(const char *cmd);
void	execute_builtin(t_cmd *cmd, t_data *data);
void	close_pipes(int *pipefd, int prev_pipefd, bool is_first, bool is_last);
void	setup_child_redirections(int *pipefd, int prev_pipefd, bool is_first, bool is_last);
void	apply_redirections(t_cmd *cmd);

// Signal handling

extern volatile sig_atomic_t	g_signal;
void	setup_signals_interactive(void);
void	setup_signals_executing(void);
void	restore_signals_default(void);

// Cleanup

void	cleanup_data(t_data *data);
void	exit_cleanup(t_data *data);

// Debug

void	debug(t_data *data);

// Built-ins

int		ed_change_directory(t_list *list, t_pwd *directory, const char *path);

void	ed_echo(const char **message);

size_t	env_namelen(const char *name);
size_t	env_valuelen(const char *str);
char	*ft_getenv(const t_list *list, const char *name);
void	env_print(const t_list *envp);
// void	env_all_print(const t_list *envp);
// void	env_single_print(const t_list *envp);

void	minishell_exit(t_data *data);

bool	is_env_name(const char *str);
void	*export_env(t_list *list, const char *envvar);
void	export_print(const t_list *list);

void	*ed_update_pwd(t_pwd *directory);
void	pwd_print(t_pwd directory);

void	unset_env(t_list **head, const char *name);

// Parsing

void	ed_cmddelone(t_cmd *cmd);
void	ed_cmdclear(t_cmd **cmd);

bool	is_redir_heredoc(const char *arg);
bool	is_redir_in(const char *arg);
bool	is_redir_out(const char *arg);
size_t	count_redir_heredoc(const char **args);
size_t	count_redir_in(const char **args);
size_t	count_redir_out(const char **args);

t_cmd	*ed_cmdnew(const char **args, size_t num);
void	ed_cmdadd_back(t_cmd **head, t_cmd *new);

t_redir	*init_redir_in(const char **args, size_t size);
t_redir	*init_redir_out(const char **args, size_t size);
t_cmd	*init_cmd(const char **args, size_t size);

t_data	*ed_parsing(t_data *data);

// HEREDOC

// heredoc_name_generator.c

void	*generate_random_pointer(size_t size);
char	*convert_mem_to_base16(const void *ptr, size_t size);
char	*generate_heredoc_name();
// heredoc_utils.c

void	heredoc_print_warning(size_t line_count, const char *delimiter);
size_t	heredoc_variable_length(const char *line);

t_data	*heredoc(t_data *data);
void	remove_heredoc_files(t_cmd *cmd);
char	**heredoc_extract_variables(const t_list *envp, const char *line);
size_t	strarrlen(const char **str_array);
char	*heredoc_expansion(const t_list *envp, const char *line);
// char	*expand_variable(t_list *envp, char *str);

#endif
