/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:34:56 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/29 10:57:45 by dbakker          ###   ########.fr       */
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
 * @return Pointer to the initialized input array, or NULL on complete failure.
 *
 * @warning Callers owns free().
 */
t_redir	*init_redir_in(const char **args)
{
	t_redir	*redir_in;
	size_t	i;
	size_t	j;

	redir_in = ft_calloc(count_redir_in(args) + 1, sizeof(t_redir));
	if (redir_in == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (args[i])
	{
		if (is_redir_in(args[i]))
		{
			redir_in[j].redir_type = get_redirection_type(args[i]);
			if (args[i + 1])
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
 * @return Pointer to the initialized output array, or NULL on complete failure.
 *
 * @warning Callers owns free().
 */
t_redir	*init_redir_out(const char **args)
{
	t_redir	*redir_out;
	size_t	i;
	size_t	j;

	redir_out = ft_calloc(count_redir_out(args) + 1, sizeof(t_redir));
	if (redir_out == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (args[i])
	{
		if (is_redir_out(args[i]))
		{
			redir_out[j].redir_type = get_redirection_type(args[i]);
			if (args[i + 1])
				redir_out[j].file = ft_strdup(args[i + 1]);
			if (redir_out[j].file == NULL)
				return (redir_out);
			j++;
		}
		i++;
	}
	return (redir_out);
}

t_cmd	*init_cmd(const char **args, size_t num)
{
	t_cmd	*redir;

	redir = ed_cmdnew(args, num);
	if (redir == NULL)
	{
		return (NULL);
	}
	redir->redirect.infile = init_redir_in((const char **)redir->args);
	redir->redirect.outfile = init_redir_out((const char **)redir->args);
	if (redir->redirect.infile == NULL || redir->redirect.outfile == NULL)
	{
		return (NULL);
	}
	return (redir);
}
