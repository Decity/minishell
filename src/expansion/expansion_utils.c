/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 19:37:03 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/03 20:06:20 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Calculate the length of @p `arg` until it encounters a non-NAME
 * @brief character.
 *
 * This function assumes that @p `arg` starts right after a `$`.
 *
 * @param[in] arg String from the command line argument.
 *
 * @return The length of @p `arg`.
 */
size_t	expansion_varlen(const char *arg)
{
	size_t	len;

	len = 0;
	if (arg[len] == '?')
	{
		return (1);
	}
	while (ft_isalnum(arg[len]) || arg[len] == '_')
	{
		len += 1;
	}
	return (len);
}

/**
 * @brief Calculate the size of @p `arg` after expanding the first variable.
 *
 * @param[in] arg	String from the command line argument.
 * @param[in] idx	Index of the first variable.
 * @param[in] data	Data struct containing the linked list of environmental
 * 					variables and most recent `exit_status`.
 *
 * @return The required size of the new string.
 */
size_t	expansion_new_strlen(const char *arg, size_t idx, const t_data *data)
{
	const size_t	arglen = ft_strlen(arg);
	const size_t	varlen = expansion_varlen(arg + idx);
	const char		*envval = ft_getnenv(data->envp, arg + idx, varlen);
	size_t			expandlen;

	if (arg[idx] == '?')
	{
		expandlen = ft_intlen(data->exit_status);
	}
	else if (envval == NULL)
	{
		expandlen = 0;
	}
	else
	{
		expandlen = ft_strlen(envval);
	}
	return (arglen - varlen + expandlen);
}
