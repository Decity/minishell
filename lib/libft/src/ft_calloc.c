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
 * @brief Allocate @p `num` times @p `size` bytes of memory.
 *
 * If @p `num` or @p `size` is 0, it will instead return a unique pointer value that can
 * be freed later.
 *
 * @param[in]	num		Number of members.
 * @param[in]	size	Size of each member
 *
 * @return Pointer to the allocated memory, or NULL on failure.
 *
 * @warning Caller owns free().
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	ptr = malloc(nmemb * size);
	if (ptr == NULL || size > SIZE_MAX / nmemb)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
