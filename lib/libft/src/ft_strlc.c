/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:36:10 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/07 15:29:12 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Copy @p src to @p dest by @p size bytes and null terminates @p dest.
 *
 * @param[in,out]	dest	String to copy to.
 * @param[in]		src		NUL-terminated string to copy from.
 * @param[in]		size	Amount to copy in bytes.
 *
 * @returns	The length of the string @p src.
 */
size_t	ft_strlcpy(char *dest, const char *src, size_t num)
{
	size_t	srclen;
	size_t	i;

	srclen = ft_strlen(src);
	if (num == 0)
	{
		return (srclen);
	}
	i = 0;
	while (i < num - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (srclen);
}

/**
 * @brief	Append string @p src to @p dest by size bytes with size-bound safety.
 *
 * @param[in,out]	dest	Destination buffer. Must be null terminated.
 * @param[in]		src		String to append.
 * @param[in]		size	Total size of the destination buffer.
 *
 * @returns	The total length of the string it tried to create and the
 * 			concatented result.
 */
size_t	ft_strlcat(char *dest, const char *src, size_t num)
{
	size_t	destlen;
	size_t	srclen;
	size_t	i;

	destlen = ft_strnlen(dest, num);
	srclen = ft_strlen(src);
	i = 0;
	if (destlen == num)
		return (srclen + num);
	while (i < num - 1 && src[i])
	{
		dest[destlen + i] = src[i];
		i++;
	}
	dest[destlen + i] = '\0';
	return (destlen + srclen);
}
