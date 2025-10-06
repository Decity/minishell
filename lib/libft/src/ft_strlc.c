/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:36:10 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/06 16:47:26 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Copy @p src to @p dst by @p size bytes and null terminates @p dst.
 *
 * @param[in,out]	dst		String to copy to.
 * @param[in]		src		NUL-terminated string to copy from.
 * @param[in]		size	Amount to copy in bytes.
 *
 * @returns	The length of the string @p src.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	i;

	srclen = ft_strlen(src);
	if (size != 0)
	{
		i = 0;
		while (i < size - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srclen);
}

/**
 * @brief	Append string @p src to @p dst by size bytes with size-bound safety.
 *
 * @param[in,out]	dst		Destination buffer. Must be null terminated.
 * @param[in]		src		String to append.
 * @param[in]		size	Total size of the destination buffer.
 *
 * @returns	The total length of the string it tried to create and the
 * 			concatented result.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	dstlen = 0;
	srclen = 0;
	i = 0;
	while (dst[dstlen] != '\0' && dstlen < size)
		dstlen++;
	while (src[srclen] != '\0')
		srclen++;
	if (dstlen == size)
		return (size + srclen);
	while (dstlen + i < size - 1 && src[i] != '\0')
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	if (dstlen + i < size)
		dst[dstlen + i] = '\0';
	return (dstlen + srclen);
}
