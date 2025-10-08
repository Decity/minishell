/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:37:29 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/08 22:06:49 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Locate the first occurrence of @p little in @p big by @p len bytes.
 *
 * @param[in,out]	big		String to read.
 * @param[in]		little	String to find in read.
 * @param[in]		len		Amount to read in bytes.
 *
 * @returns	Pointer to the first character of the first occurrence of
 * 			@p little, `NULL` if there is no occurrence, or pointer to @p big if
 * 			@p little is an empty string.
 */
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*little == '\0')
		return ((char *)big);
	while (i < len && big[i] != '\0')
	{
		j = 0;
		while (little[j] != '\0' && big[i + j] == little[j] && (i + j) < len)
			j++;
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
