/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:37:29 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/09 11:04:13 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Find @p `needle` in @p `haystack` within the first @p `num` bytes.
 *
 * `NULL` will be returned if @p `num` is smaller than than the length of
 * @p `needle`.
 *
 * @param[in] haystack	The haystack.
 * @param[in] needle	The needle to find in @p `haystack`.
 * @param[in] num		Amount to read in bytes.
 *
 * @retval Pointer to @p `haystack` if @p `needle` is empty.
 * @retval Pointer to the first occurrence of @p `needle` in @p `haystack`.
 * @retval `NULL` if @p `needle` is not found in @p `haystack`.
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t num)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[j] == '\0')
	{
		return ((char *)haystack);
	}
	while (i < num && haystack[i] != '\0')
	{
		j = 0;
		while (needle[j] && haystack[i + j] == needle[j] && (i + j) < num)
		{
			j++;
		}
		if (needle[j] == '\0')
		{
			return ((char *)&haystack[i]);
		}
		i++;
	}
	return (NULL);
}
