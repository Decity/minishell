/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:14:19 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/26 12:07:43 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @return `true` if @p `arg` is `<` or `<<`, `false` otherwise.
 */
bool	is_redir_in(const char *arg)
{
	if (*arg == '<' || ft_strncmp(arg, "<<", ft_strlen(arg)) == 0)
	{
		return (true);
	}
	return (false);
}

/**
 * @return `true` if @p `arg` is `>` or `>>`, `false` otherwise.
 */
bool	is_redir_out(const char *arg)
{
	if (*arg == '>' || ft_strncmp(arg, ">>", ft_strlen(arg)) == 0)
	{
		return (true);
	}
	return (false);
}

/**
 * @brief Count how many `<` and `<<` are found in @p `args`.
 *
 * @param[in] args Array of strings.
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
			input_count++;
		}
		i++;
	}
	return (input_count);
}

/**
 * @brief Count how many `>` and `>>` are found in @p `args`.
 *
 * @param[in] args Array of strings.
 *
 * @return Amount of `>` and `>>` found in @p `args`.
 */
size_t	count_redir_out(const char **args)
{
	size_t	i;
	size_t	output_count;

	i = 0;
	output_count = 0;
	while (args[i])
	{
		if (is_redir_out(args[i]))
		{
			output_count++;
		}
		i++;
	}
	return (output_count);
}