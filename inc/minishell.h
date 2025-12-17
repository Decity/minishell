/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:08:30 by ebelle            #+#    #+#             */
/*   Updated: 2025/12/17 13:54:55 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L

// headers
# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"
# include "../libft/inc/get_next_line.h"
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
void	set_redirections(t_data *data);
void	close_redirection_fds(t_data *data);

// Parsing
bool	is_redirection(char *str);

// TOKENIZATION

// tokenization_normalization_strlen.c

void	tokenization_update_tokens(const char *str, int8_t *curr_type,
			int8_t *next_type);

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

// tokenization_validation_utils.c
void	skip_quoted_section(char *input, size_t *i);

/// EXECUTION

char	*get_executable_path(const char *exec, const t_list *envp);
size_t	get_cmds_count(t_cmd *commands);
void	execution(t_data *data);
void	handle_pipeline(t_data *data);
void	handle_single_cmd(t_cmd *cmd, t_data *data);
void	handle_single_builtin(t_cmd *cmd, t_data *data);
void	execute_binary(t_cmd *cmd, t_data *data);
void	execute_child(t_cmd *cmd, t_data *data);
char	*get_bin_path(t_cmd *cmd, t_data *data);
bool	is_builtin(const char *cmd);
int		execute_builtin(t_cmd *cmd, t_data *data);
void	close_pipes(int *pipefd, int prev_pipefd, bool is_first, bool is_last);
void	setup_child_redirections(int *pipefd, int prev_pipefd, bool is_first,
			bool is_last);
int		apply_redirections(t_cmd *cmd);
void	exec_pipeline_child(t_cmd *cmd, t_data *data, t_pnp *pnp,
			bool is_first);
void	wait_for_children(pid_t *pids, size_t count, t_data *data);
void	cleanup_pipeline(pid_t *pids, size_t count);
void	handle_fork_error(pid_t *pids, size_t i, int *pipefd, t_data *data);
void	close_parent_pipes(size_t i, int prev_pipefd, int *pipefd,
			t_cmd *current);
void	init_pipeline(t_data *data, t_pnp *pnp);
void	handle_pipe_creation(t_cmd *current, t_pnp *pnp, t_data *data,
			size_t i);
void	fork_and_execute(t_cmd *current, t_pnp *pnp, size_t i, t_data *data);

// Signal handling

extern volatile sig_atomic_t	g_signal;

void	setup_signals_interactive(void);
void	setup_signals_executing(void);
void	restore_signals_default(void);

// Cleanup

void	cleanup_data(t_data *data);
void	full_cleanup(t_data *data);
void	exit_cleanup(t_data *data, int exit_code);

// BUILTINS

// cd.c

int		builtin_cd(t_list *envp, t_pwd *dir, const char *path);
// echo.c

int		builtin_echo(const char **messages);
// env.c

size_t	env_namelen(const char *name);
size_t	env_valuelen(const char *str);
char	*ft_getenv(const t_list *list, const char *name);
char	*ft_getnenv(const t_list *list, const char *name, size_t num);
int		builtin_env_print(const t_list *envp);
// exit.c

void	builtin_exit(t_cmd *cmd, t_data *data);
// export_print.c

int		builtin_export(t_list *envp, char **args);
int		export_print(const t_list *list);
int		handle_export(t_cmd *cmd, t_data *data);
int		builtin_export_var(t_list *envp, char *envvar);
// pwd.c

void	*builtin_update_pwd(t_pwd *directory);
int		pwd_print(t_pwd directory);
// unset.c

int		builtin_unset(t_list **head, char **args);
// PARSING

// parsing_linked_list.c

t_cmd	*cmdnew(const char **args, size_t num);
void	cmdadd_back(t_cmd **head, t_cmd *new);
void	cmddelone(t_cmd *cmd);
void	cmdclear(t_cmd **cmd);
void	redirclear(t_redir *redir);
// parsing_redirection_in.c

bool	is_redir_heredoc(const char *arg);
bool	is_redir_in(const char *arg);
size_t	count_redir_heredoc(const char **args);
size_t	count_redir_in(const char **args);
// parsing_redirection_out.c

bool	is_redir_out(const char *arg);
size_t	count_redir_out(const char **args);
// parsing_redirection.c

t_cmd	*parsing_init(const char **args, size_t size);
// parsing.c

int		parsing(t_data *data);

// HEREDOC

// heredoc_expansion_utils.c

char	*heredoc_expand(const t_list *envp, const char *name);
char	*heredoc_copy_line(char *dest, const char *src);
size_t	heredoc_copy_variable(char *dest, const char *src);
// heredoc_expansion.c

char	*heredoc_expansion(const t_list *envp, const char *line);
// heredoc_name_generator.c

void	*generate_random_pointer(size_t size);
char	*convert_mem_to_base16(const void *ptr, size_t size);
char	*generate_heredoc_name(void);
// heredoc_utils.c

void	heredoc_print_warning(size_t line_count, const char *delimiter);
size_t	heredoc_variable_length(const char *line);
char	*heredoc_duplicate(const char *line);
void	remove_heredoc_files(t_cmd *cmd);
// heredoc.c

int		heredoc(t_data *data);

// EXPANSION

// expansion_copy.c

char	*expansion_copy(char *dest, const char *src, const char *envval);
// expansion_remove_quotes.c

char	*expansion_remove_quotation(char *str);
// expansion_utils.c

size_t	expansion_varlen(const char *arg);
size_t	expansion_new_strlen(const char *arg, size_t idx, const t_data *data);
// expansion.c

int		expansion(t_data *data);
#endif
