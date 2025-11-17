/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:34:56 by dbakker           #+#    #+#             */
/*   Updated: 2025/11/15 12:29:40 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hd	*init_redir_heredoc(const char **args, size_t size)
{
	t_hd	*heredoc;
	size_t	i;
	size_t	j;

	heredoc = ft_calloc(count_redir_heredoc(args) + 1, sizeof(t_hd));
	if (heredoc == NULL)
	{
		return (NULL);
	}
	i = 0;
	j = 0;
	while (i < size && args[i])
	{
		if (is_redir_heredoc(args[i]))
		{
			heredoc[j].delimiter = ft_strdup(args[i + 1]);
			if (heredoc[j].delimiter == NULL)
				return (NULL);
			j++;
		}
		i++;
	}
	return (heredoc);
}

/**
 * @brief Initialize an array of input redirections with their types
 *
 * Scans the argument array for input redirections (< or <<) and creates
 * an array storing the redirection type and target filename. Returns a
 * partial result if string duplication fails.
 *
 * @param[in] args Array of command arguments
 * @param[in] size Number of arguments to process
 *
 * @return Pointer to array of input redirections, or NULL on complete failure
 *
 * @warning Caller owns free()
 */
t_redir	*init_redir_in(const char **args, size_t size)
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
			redir_in[j].file = ft_strdup(args[i + 1]);
			if (redir_in[j].file == NULL)
				return (redir_in);
			j++;
		}
		i++;
	}
	return (redir_in);
}

/**
 * @brief Initialize an array of output redirections with their types
 *
 * Scans the argument array for output redirections (> or >>) and creates
 * an array storing the redirection type and target filename. Returns a
 * partial result if string duplication fails.
 *
 * @param[in] args Array of command arguments
 * @param[in] size Number of arguments to process
 *
 * @return Pointer to array of output redirections, or NULL on complete failure
 *
 * @warning Caller owns free()
 */
t_redir	*init_redir_out(const char **args, size_t size)
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
				return (redir_out);
			j++;
		}
		i++;
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
size_t	ed_args_size(const char **args, size_t size)
{
	size_t	array_size;
	size_t	i;

	array_size = 0;
	i = 0;
	while (args[i] && i < size)
	{
		if (get_redirection_type(args[i]) == 0)
		{
			array_size++;
		}
		else
		{
			i++;
		}
		i++;
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
char	**trim_redirections(const char **args, size_t size)
{
	char	**trimmed;
	size_t	array_size;
	size_t	i;

	trimmed = ft_calloc(ed_args_size(args, size) + 1, sizeof(char *));
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
				return (ft_free2d((void **)trimmed, array_size), NULL);
			array_size++;
		}
		else
		{
			i++;
		}
		i++;
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
t_cmd	*init_cmd(const char **args, size_t size)
{
	t_cmd	*redir;
	char	**trimmed;

	trimmed = trim_redirections(args, size);
	redir = ed_cmdnew((const char **)trimmed, size);
	if (redir == NULL)
	{
		return (NULL);
	}
	redir->redirect.heredoc = init_redir_heredoc(args, size);
	redir->redirect.infile = init_redir_in(args, size);
	redir->redirect.outfile = init_redir_out(args, size);
	return (redir);
}
