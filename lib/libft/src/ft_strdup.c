/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:48:56 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/09 10:59:48 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copy @p `str` to a new memory address.
 *
 * @param[in] str String to duplicate.
 *
 * @return Pointer to the duplicated string, or `NULL` on failure.
 *
 * @warning Caller owns free().
 */
char	*ft_strdup(const char *str)
{
	const size_t	strlen = ft_strlen(str);
	char			*ptr;

	ptr = ft_calloc(strlen + 1, sizeof(char));
	if (ptr == NULL)
	{
		return (NULL);
	}
	return (ft_memcpy(ptr, str, strlen));
}

/**
 * @brief Copy @p `num` bytes of @p `str` to a new memory address.
 *
 * @param[in] str String to duplicate.
 * @param[in] num Amount of bytes to duplicate.
 *
 * @return Pointer to the duplicated string, or `NULL` on failure.
 *
 * @warning Callers owns free().
 */
char	*ft_strndup(const char *str, size_t num)
{
	const size_t	strlen = ft_strlen(str);
	char			*ptr;

	if (strlen < num)
	{
		num = strlen;
	}
	ptr = ft_calloc(num + 1, sizeof(char));
	if (ptr == NULL)
	{
		return (NULL);
	}
	return (ft_memcpy(ptr, str, num));
}
