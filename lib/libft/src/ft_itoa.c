/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:09:08 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/06 22:17:19 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Convert a 32-bit integer to a string.
 *
 * @param[in] num The integer to convert.
 *
 * @return The converted string, or NULL on failure.
 *
 * @warning Caller owns free().
 */
char	*ft_itoa(int32_t num)
{
	char	*ptr;
	int64_t	nbr;
	size_t	len;

	len = ft_intlen(num);
	nbr = num;
	ptr = ft_calloc(len + 1, sizeof(char));
	if (ptr == NULL)
		return (NULL);
	if (num == 0)
		ptr[0] = '0';
	if (num < 0)
	{
		ptr[0] = '-';
		nbr = -nbr;
	}
	while (nbr > 0)
	{
		ptr[--len] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (ptr);
}
