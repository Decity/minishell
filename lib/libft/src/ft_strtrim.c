/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:09:28 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/09 10:30:20 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Return a new string from trimming the start and end of @p `str` with
 * @brief characters found in @p `set`.
 *
 * @param[in] str String to trim.
 * @param[in] set Set of characters.
 *
 * @return Pointer to the newly allocated trimmed string, or `NULL` on failure.
 *
 * @warning	Caller owns free().
 */
char	*ft_strtrim(char const *str, char const *set)
{
	size_t	end;
	size_t	start;
	char	*trim;

	if (str == NULL || set == NULL)
	{
		return (NULL);
	}
	start = 0;
	end = ft_strlen(str);
	while (str[start] && ft_strchr(set, str[start]))
	{
		str++;
	}
	if (start == end)
		return (ft_calloc(1, sizeof(char)));
	while (end > 0 && ft_strchr(set, str[end - 1]))
	{
		end--;
	}
	trim = ft_calloc(end - start + 1, sizeof(char));
	if (trim == NULL)
		return (NULL);
	return (ft_memcpy(trim, str + start, end - start));
}
