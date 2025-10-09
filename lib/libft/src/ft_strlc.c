/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:36:10 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/09 10:59:58 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copy @p `num` - 1 bytes from @p `src` to @p `dest` and null
 * @brief terminate the result.
 *
 * @param[out]	dest	String to copy to.
 * @param[in]	src		Null terminated string to copy from.
 * @param[in]	size	Amount in bytes to copy.
 *
 * @return The length of @p `src`.
 */
size_t	ft_strlcpy(char *dest, const char *src, size_t num)
{
	const size_t	srclen = ft_strlen(src);
	size_t			i;

	if (num == 0)
	{
		return (srclen);
	}
	i = 0;
	while (src[i] && i < num - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (srclen);
}

/**
 * @brief Append @p `num` - 1 bytes of @p `str` to @p `dest`.
 *
 * @param[in,out]	dest	Null terminated string to append to.
 * @param[in]		src		Null terminated string to copy from.
 * @param[in]		size	Total byte size of @p `dest`.
 *
 * @return The total length of the string it tried to create and the
 * @return concatented result.
 */
size_t	ft_strlcat(char *dest, const char *src, size_t num)
{
	const size_t	destlen = ft_strnlen(dest, num);
	const size_t	srclen = ft_strlen(src);
	size_t			i;

	i = 0;
	if (destlen == num)
	{
		return (num + srclen);
	}
	while (src[i] && destlen + i < num - 1)
	{
		dest[destlen + i] = src[i];
		i++;
	}
	dest[destlen + i] = '\0';
	return (destlen + srclen);
}
