/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfnd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:48:26 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/07 14:52:35 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Return a pointer to the first occurrence of character @p c in @p str.
 *
 * @param[in]	str	The string to read.
 * @param[in]	c	The character to find.
 *
 * @returns	Pointer to the matching byte @p c, or NULL if not found.
 *
 * @warning	This function does not work with wide or multibyte characters.
 *
 * @note	The terminating null byte is considered part of the string.
 */
char	*ft_strchr(const char *str, int character)
{
	size_t	i;
	char	*cpystr;

	i = 0;
	cpystr = (char *)str;
	while (cpystr[i] != '\0' && cpystr[i] != character)
		i++;
	if (cpystr[i] == character)
		return (cpystr + i);
	return (NULL);
}

/**
 * @brief	Return a pointer to the last occurrence of character @p c in @p str.
 *
 * @param[in]	str	The string to read.
 * @param[in]	c	The character to find.
 *
 * @returns	Pointer to the matching byte @p c, or NULL if not found.
 *
 * @warning	This function does not work with wide or multibyte characters.
 *
 * @note	The terminating null byte is considered part of the string.
 */
char	*ft_strrchr(const char *str, int c)
{
	const char	*cpystr;
	size_t	i;

	cpystr = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			cpystr = &str[i];
		i++;
	}
	if (str[i] == (unsigned char)c)
		return ((char *)str + i);
	return ((char *)cpystr);
}
