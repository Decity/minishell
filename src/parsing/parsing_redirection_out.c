/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection_out.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:29:03 by dbakker           #+#    #+#             */
/*   Updated: 2025/11/29 18:08:01 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @return `true` if @p `arg` is `>` or `>>`, `false` otherwise.
 */
bool	is_redir_out(const char *arg)
{
	if (ft_strncmp(arg, ">", 2) == 0 || ft_strncmp(arg, ">>", 3) == 0)
	{
		return (true);
	}
	return (false);
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
			output_count += 1;
		}
		i += 1;
	}
	return (output_count);
}
