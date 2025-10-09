/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:28:23 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/09 10:59:43 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Return a substring with a maxmimum length of @p `num` bytes
 * @brief from @p `str` starting at @p `start`.
 *
 * @param[in] str	String to create the substring from.
 * @param[in] start	Starting index.
 * @param[in] num	Maximum length of the substring.
 *
 * @return Pointer to the substring, or `NULL` on failure.
 *
 * @warning Caller owns free().
 */
char	*ft_substr(const char *str, uint32_t start, size_t num)
{
	const size_t	strlen = ft_strlen(str);
	size_t			i;
	char			*ptr;

	if (str == NULL)
	{
		return (NULL);
	}
	if (start > strlen)
	{
		return (ft_calloc(1, sizeof(char)));
	}
	i = 0;
	if (num > strlen + start)
	{
		num = strlen + start;
	}
	ptr = ft_calloc(num + 1, sizeof(char));
	if (ptr == NULL)
	{
		return (NULL);
	}
	return (ft_memcpy(ptr, str + start, num));
}
