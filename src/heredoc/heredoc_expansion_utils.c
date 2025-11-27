/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:38:50 by dbakker           #+#    #+#             */
/*   Updated: 2025/11/27 22:32:22 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @return The expanded variable of @p `envvar`, or `NULL` on failure.
 *
 * @warning Caller owns `free()`.
 */
char	*heredoc_expand(const t_list *envp, const char *envvar)
{
	// TODO: Expand $?
	if (ft_getenv(envp, envvar) == NULL)
	{
		return (ft_strdup(""));
	}
	return (ft_strdup(ft_getenv(envp, envvar)));
}

/**
 *
 */
size_t	heredoc_copy_line(char *strret, const char *src)
{
	const char	*envvar = ft_strchr(src, '$');
	size_t		num;

	if (envvar == NULL)
	{
		num = ft_strlen(src);
	}
	else
	{
		num = envvar - src;
	}
	if (num)
	{
		ft_memcpy(strret, src, num);
	}
	if (envvar == NULL)
	{
		src = src + num;
	}
	else
	{
		src = envvar;
	}
	return (src);
}

/**
 *
 */
size_t	heredoc_copy_variable(char *strret, const char *src)
{
	const size_t	slen = ft_strlen(src);

	if (slen)
	{
		ft_memcpy(strret, src, slen);
	}
	return (slen);
}
