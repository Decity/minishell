/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:39:19 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/06 16:47:26 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Allocate memory and initialize it to zero.
 *
 * @param[in]	nmemb	Number of members.
 * @param[in]	size	Size of each member in bytes.
 *
 * @returns	Pointer to the allocated memory or NULL on failure.
 *
 * @warning	The caller owns free() when done.
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	ptr = malloc(nmemb * size);
	if (ptr == NULL || size > __SIZE_MAX__ / nmemb)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
