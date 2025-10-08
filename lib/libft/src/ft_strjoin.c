/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:38:07 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/08 22:40:54 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Return a new string from joining @p `dest` and @p `src` together.
 *
 * @param[in]	dest	The prefix string.
 * @param[in]	src		The suffix string.
 *
 * @return Pointer to the joined string, or `NULL` on failure.
 *
 * @warning Caller owns free().
 */
char	*ft_strjoin(const char *dest, const char *src)
{
	size_t	srclen;
	size_t	destlen;
	char	*join;

	if (dest == NULL || src == NULL)
	{
		return (NULL);
	}
	destlen = ft_strlen(dest);
	srclen = ft_strlen(src);
	join = ft_calloc(destlen + srclen + 1, sizeof(char));
	if (join == NULL)
	{
		return (NULL);
	}
	ft_memcpy(join, dest, destlen);
	ft_memcpy(join + destlen, src, srclen);
	return (join);
}
