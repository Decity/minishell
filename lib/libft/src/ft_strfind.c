/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:48:26 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/09 11:03:13 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Return a pointer to the first occurrence of
 * @brief @p `character` in @p `str`.
 *
 * The terminating null byte is part of @p `str`.
 *
 * @param[in] str		The string to read.
 * @param[in] character	The character to find.
 *
 * @returns	Pointer to the matching @p `character`, or `NULL` if not found.
 */
char	*ft_strchr(const char *str, int character)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != character)
	{
		i++;
	}
	if (str[i] == character)
	{
		return ((char *)str + i);
	}
	return (NULL);
}

/**
 * @brief Return a pointer to the last occurrence of @p `character` in @p `str`.
 *
 * The terminating null byte is considered part of the string, but behaves
 * like ft_strchr().
 *
 * @param[in] str		The string to read.
 * @param[in] character	The character to find.
 *
 * @returns	Pointer to the matching @p `character`, or `NULL` if not found.
 */
char	*ft_strrchr(const char *str, int character)
{
	size_t	i;
	char	*last;

	i = 0;
	last = NULL;
	while (str[i])
	{
		if (str[i] == character)
		{
			last = (char *)str + i;
		}
		i++;
	}
	if (str[i] == character)
	{
		return ((char *)str + i);
	}
	return (last);
}
