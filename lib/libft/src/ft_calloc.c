/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:39:19 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/09 15:29:29 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocate @p `num` times @p `size` bytes of memory and initializes the
 * @brief allocated memory to 0.
 *
 * If @p `num` or @p `size` is 0, it will instead return a unique pointer value
 * that can be freed later.
 *
 * @param[in] num	Number of members.
 * @param[in] size	Size of each member.
 *
 * @return Pointer to the allocated memory, or `NULL` on failure.
 *
 * @warning Caller owns free().
 */
void	*ft_calloc(size_t num, size_t size)
{
	void	*ptr;

	if (num == 0 || size == 0)
	{
		return (malloc(0));
	}
	ptr = malloc(num * size);
	if (ptr == NULL || size > SIZE_MAX / num)
	{
		return (NULL);
	}
	ft_bzero(ptr, num * size);
	return (ptr);
}
