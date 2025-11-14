/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:34:56 by dbakker           #+#    #+#             */
/*   Updated: 2025/11/14 15:57:01 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initialize an array of input files along with the respective
 * @brief redirection type.
 *
 * A pointer will still be returned even if the duplication of one the strings
 * fails.
 *
 * @param[in] args Array of strings.
 *
 * @return Pointer to the initialized input array, or `NULL` on complete failure.
 *
 * @warning Caller owns free().
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
 * @brief Initialize an array of output files along with the respective
 * @brief redirection type.
 *
 * A pointer will still be returned even if the duplication of one the strings
 * fails.
 *
 * @param[in] args Array of strings.
 *
 * @return Pointer to the initialized output array, or `NULL` on complete
 * @return failure.
 *
 * @warning Caller owns free().
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
 * @return The amount of arguments excluding all redirections and filenames.
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
 * @brief Create a new string with the redirections and filenames removed.
 *
 * @param[in] args Array of strings.
 *
 * @return Pointer to the array of strings with the redirections removed,
 * @return or `NULL` on failure.
 *
 * @warning Caller owns free().
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
 * @brief Initialize the command struct with @p `size` tokens from @p `args`.
 *
 * @param[in] args Array of strings.
 * @param[in] size Amount of strings to copy to the command struct.
 *
 * @return Pointer to the new command struct, or `NULL` on complete failure.
 *
 * @warning Caller owns free.
 *
 * @note A pointer still gets returned even if redirections fail.
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
	redir->redirect.infile = init_redir_in(args, size);
	redir->redirect.outfile = init_redir_out(args, size);
	return (redir);
}
