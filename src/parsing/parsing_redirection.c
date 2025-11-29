/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:34:56 by dbakker           #+#    #+#             */
/*   Updated: 2025/11/29 19:44:54 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initialize an array of input redirections with their types
 *
 * Scans the argument array for input redirections (< or <<) and creates
 * an array storing the redirection type and target filename/delimiter.
 *
 * @param[in] args Array of command arguments
 * @param[in] size Number of arguments to process
 *
 * @return Pointer to array of input redirections, or `NULL` on failure.
 *
 * @warning Caller owns `free()`.
 */
static t_redir	*parsing_init_redir_in(const char **args, size_t size)
{
	t_redir	*redir_in;
	size_t	i;
	size_t	j;

	redir_in = ft_calloc(count_redir_in(args) + 1, sizeof(t_redir));
	if (redir_in == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (args[i] && i < size)
	{
		if (is_redir_in(args[i]))
		{
			redir_in[j].redir_type = get_redirection_type(args[i]);
			if (redir_in[j].redir_type == TYPE_REDIRECTION_HEREDOC)
				redir_in[j].delimiter = ft_strdup(args[i + 1]);
			else
				redir_in[j].file = ft_strdup(args[i + 1]);
			if (redir_in[j].file == NULL && redir_in[j].delimiter == NULL)
				return (NULL);
			j += 1;
		}
		i += 1;
	}
	return (redir_in);
}

/**
 * @brief Initialize an array of output redirections with their types
 *
 * Scans the argument array for output redirections (> or >>) and creates
 * an array storing the redirection type and target filename.
 *
 * @param[in] args Array of command arguments
 * @param[in] size Number of arguments to process
 *
 * @return Pointer to array of output redirections, or `NULL` on failure.
 *
 * @warning Caller owns `free()`,
 */
static t_redir	*parsing_init_redir_out(const char **args, size_t size)
{
	t_redir	*redir_out;
	size_t	i;
	size_t	j;

	redir_out = ft_calloc(count_redir_out(args) + 1, sizeof(t_redir));
	if (redir_out == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (args[i] && i < size)
	{
		if (is_redir_out(args[i]))
		{
			redir_out[j].redir_type = get_redirection_type(args[i]);
			redir_out[j].file = ft_strdup(args[i + 1]);
			if (redir_out[j].file == NULL)
				return (NULL);
			j += 1;
		}
		i += 1;
	}
	return (redir_out);
}

/**
 * @brief Count arguments excluding redirections and their target files
 *
 * @param[in] args Array of command arguments
 * @param[in] size Number of arguments to process
 *
 * @return Number of non-redirection arguments
 */
static size_t	parsing_args_size(const char **args, size_t size)
{
	size_t	array_size;
	size_t	i;

	array_size = 0;
	i = 0;
	while (args[i] && i < size)
	{
		if (get_redirection_type(args[i]) == 0)
		{
			array_size += 1;
		}
		else
		{
			i += 1;
		}
		i += 1;
	}
	return (array_size);
}

/**
 * @brief Create a new array with redirections and target files removed
 *
 * @param[in] args Array of command arguments
 * @param[in] size Number of arguments to process
 *
 * @return Pointer to new array without redirections, or NULL on failure
 *
 * @warning Caller owns free()
 */
static char	**parsing_trim_redirections(const char **args, size_t size)
{
	char	**trimmed;
	size_t	array_size;
	size_t	i;

	trimmed = ft_calloc(parsing_args_size(args, size) + 1, sizeof(char *));
	if (trimmed == NULL)
		return (NULL);
	array_size = 0;
	i = 0;
	while (args[i] && i < size)
	{
		if (get_redirection_type(args[i]) == 0)
		{
			trimmed[array_size] = ft_strdup(args[i]);
			if (trimmed[array_size] == NULL)
				return (free_array(&trimmed), NULL);
			array_size += 1;
		}
		else
		{
			i += 1;
		}
		i += 1;
	}
	return (trimmed);
}

/**
 * @brief Initialize a command struct from argument tokens
 *
 * Creates a command struct with arguments trimmed of redirections and
 * separate arrays for input/output redirections. Returns partial result
 * if redirection initialization fails.
 *
 * @param[in] args Array of command arguments
 * @param[in] size Number of arguments to process
 *
 * @return Pointer to new command struct, or NULL on complete failure
 *
 * @warning Caller owns free()
 */
t_cmd	*parsing_init(const char **args, size_t size)
{
	t_cmd	*cmd;
	char	**trimmed;

	trimmed = parsing_trim_redirections(args, size);
	cmd = cmdnew((const char **)trimmed, size);
	free_array(&trimmed);
	if (cmd == NULL)
	{
		return (NULL);
	}
	cmd->redirect.infile = parsing_init_redir_in(args, size);
	cmd->redirect.outfile = parsing_init_redir_out(args, size);
	if (cmd->redirect.infile == NULL || cmd->redirect.outfile == NULL)
	{
		return (NULL);
	}
	return (cmd);
}
