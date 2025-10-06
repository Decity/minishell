/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:28:23 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/06 16:47:26 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Return a substring from @p str starting at @p start with a maximum
 * 			length of @p len.
 *
 * @param[in]	str		String to create the substring from.
 * @param[in]	start	Starting index within @p str.
 * @param[in]	len		Maximum length of the substring.
 *
 * @returns	Pointer to the substring, or NULL on failure.
 *
 * @warning	The caller owns free() when done.
 */
char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	if (start > ft_strlen(str))
	{
		ptr = ft_calloc(1, sizeof(char));
		if (ptr == NULL)
			return (NULL);
		return (ptr);
	}
	i = 0;
	if (len > ft_strlen(str + start))
		len = ft_strlen(str + start);
	ptr = malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	while (i < len)
		ptr[i++] = str[start++];
	ptr[len] = '\0';
	return (ptr);
}
