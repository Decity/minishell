/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:09:28 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/06 16:47:26 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Return a new string from @p str with characters removed from the
 * 			start and end of @p set
 *
 * @param[in]	str
 * @param[in]	set
 *
 * @warning	The caller owns free() when done.
 */
char	*ft_strtrim(char const *str, char const *set)
{
	char	*ptr;
	size_t	strlen;

	while (*str != '\0' && ft_strchr(set, *str))
		str++;
	strlen = ft_strlen(str);
	while (strlen > 0 && ft_strchr(set, str[strlen - 1]))
		strlen--;
	ptr = malloc(strlen + 1);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, str, strlen + 1);
	return (ptr);
}
