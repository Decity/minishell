/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:38:50 by dbakker           #+#    #+#             */
/*   Updated: 2025/11/28 10:05:48 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @return The expanded variable of @p `name`, or `NULL` on failure.
 *
 * @warning Caller owns `free()`.
 */
char	*heredoc_expand(const t_list *envp, const char *name)
{
	if (ft_getenv(envp, name) == NULL)
	{
		return (ft_strdup(""));
	}
	return (ft_strdup(ft_getenv(envp, name)));
}

/**
 * @brief Copy from @p `src` to @p `dest` until a variable is encountered.
 *
 * @param[out]	dest	String to copy to.
 * @param[in]	src		String to copy from.
 *
 * @return Pointer to @p `src`.
 */
char	*heredoc_copy_line(char *dest, const char *src)
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
		ft_memcpy(dest, src, num);
	}
	if (envvar == NULL)
	{
		src = src + num;
	}
	else
	{
		src = envvar;
	}
	return ((char *)src);
}

/**
 * @brief Copy the variable from @p `src` to @p `dest`.
 *
 * @param[out]	dest	String to copy to.
 * @param[in]	src		String to copy from.
 *
 * @return The length of @p `src`.
 */
size_t	heredoc_copy_variable(char *dest, const char *src)
{
	const size_t	slen = ft_strlen(src);

	if (slen)
	{
		ft_memcpy(dest, src, slen);
	}
	return (slen);
}
