/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection_in.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:14:19 by dbakker           #+#    #+#             */
/*   Updated: 2025/11/29 18:07:26 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @return `true` if @p `arg` is `<<`, `false` otherwise.
 */
bool	is_redir_heredoc(const char *arg)
{
	if (ft_strncmp(arg, "<<", 3) == 0)
	{
		return (true);
	}
	return (false);
}

/**
 * @return `true` if @p `arg` is `<` or `<<`, `false` otherwise.
 */
bool	is_redir_in(const char *arg)
{
	if (ft_strncmp(arg, "<", 2) == 0 || ft_strncmp(arg, "<<", 3) == 0)
	{
		return (true);
	}
	return (false);
}

/**
 * @brief Count how many `<<` are found in @p `args`.
 *
 * @param[in] args Array of arguments.
 *
 * @return Amount of `<<` found in @p `args`.
 */
size_t	count_redir_heredoc(const char **args)
{
	size_t	i;
	size_t	heredoc_count;

	i = 0;
	heredoc_count = 0;
	while (args[i])
	{
		if (is_redir_heredoc(args[i]))
		{
			heredoc_count += 1;
		}
		i += 1;
	}
	return (heredoc_count);
}

/**
 * @brief Count how many `<` and `<<` are found in @p `args`.
 *
 * @param[in] args Array of arguments.
 *
 * @return Amount of `<` and `<<` found in @p `args`.
 */
size_t	count_redir_in(const char **args)
{
	size_t	i;
	size_t	input_count;

	i = 0;
	input_count = 0;
	while (args[i])
	{
		if (is_redir_in(args[i]))
		{
			input_count += 1;
		}
		i += 1;
	}
	return (input_count);
}
