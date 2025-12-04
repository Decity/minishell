/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 19:38:22 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/04 12:00:06 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Copy @p `src` to @p `dest` up until the first `$` character.
 */
static void	expansion_copy_before_variable(char *dest, const char *src)
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
	ft_memcpy(dest, src, num);
}

/**
 * @brief Copy the expanded variable of @p `src` to @p `dest`.
 */
static void	expansion_copy_variable(char *dest, const char *src)
{
	const size_t	destlen = ft_strlen(dest);
	const size_t	srclen = ft_strlen(src);

	ft_memcpy(dest + destlen, src, srclen);
}

/**
 * @brief Copy @p `src` to @p `dest` after the first variable.
 */
static void	expansion_copy_after_variable(char *dest, const char *src)
{
	const size_t	destlen = ft_strlen(dest);
	char			*envvar;
	size_t			envvarlen;

	envvar = ft_strchr(src, '$') + 1;
	envvar += expansion_varlen(envvar);
	envvarlen = ft_strlen(envvar);
	ft_memcpy(dest + destlen, envvar, envvarlen);
}

/**
 * @brief Copy @p `src` to @p `dest, with the first occurence of a variable in
 * @brief @p `src` being substituted for @p `envval`.
 *
 * @return Pointer to @p `dest`.
 */
char	*expansion_copy(char *dest, const char *src, const char *envval)
{
	expansion_copy_before_variable(dest, src);
	expansion_copy_variable(dest, envval);
	expansion_copy_after_variable(dest, src);
	return (dest);
}
