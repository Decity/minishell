/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:55:06 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/08 23:17:36 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @return The length of @p `str`, excluding the null byte.
 *
 * @warning ft_strlen() causes the program to segfault if @p `str` is `NULL`.
 */
size_t	ft_strlen(const char *str)
{
	size_t	strlen;

	strlen = 0;
	while (str[strlen])
	{
		strlen++;
	}
	return (strlen);
}

/**
 * @brief Return the number of bytes in @p `str` excluding the null byte,
 * @brief with at most @p `maxlen`.
 *
 * @param[in]	str		String to calculate the lenght of.
 * @param[in]	maxlen	Maximum amount of bytes to read.
 *
 * @return The length of @p `str` if less than @p `maxlen`, or @p `maxlen` if
 * @return no null byte has been found.
 *
 * @warning ft_strnlen() causes the program to segfault if @p `str` is `NULL`.
 */
size_t	ft_strnlen(const char *str, size_t maxlen)
{
	size_t	strlen;

	strlen = 0;
	while (str[strlen] && strlen < maxlen)
	{
		strlen++;
	}
	return (strlen);
}
