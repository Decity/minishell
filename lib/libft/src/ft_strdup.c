/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:48:56 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/07 14:34:40 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Return a pointer to the new string duplicated from @p str.
 *
 * @param[in]	str String to duplicate.
 *
 * @returns	Pointer to the duplicated string, or NULL on failure.
 *
 * @warning	The caller owns free() when done.
 */
char	*ft_strdup(const char *str)
{
	char	*ptr;
	size_t	strlen;

	strlen = ft_strlen(str);
	ptr = ft_calloc(strlen + 1, sizeof(char));
	if (ptr == NULL)
		return (NULL);
	return (ft_memcpy(ptr, str, strlen));
}

char	*ft_strndup(const char *str, size_t num)
{
	char	*ptr;
	size_t	strlen;

	strlen = ft_strlen(str);
	if (ft_strlen(str) < num)
		ptr = ft_calloc(strlen + 1, sizeof(char));
	else
		ptr = ft_calloc(num + 1, sizeof(char));
	if (ptr == NULL)
		return (NULL);
	return (ft_memcpy(ptr, str, num));
}