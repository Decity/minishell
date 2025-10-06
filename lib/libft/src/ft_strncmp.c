/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:33:33 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/06 16:47:26 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Compare the first @p n bytes of the strings @p str1 and @p str2.
 *
 * @param[in]	str1	String to compare to @p str2.
 * @param[in]	str2	String to compare to @p str1.
 * @param[in]	n		Characters to read in bytes.
 *
 * @returns	Nonzero value by the sign of the difference between the first pair
 * 			of bytes that differ in @p str1 and @p str2, or 0 if no difference.
 *
 * @retval	0 if @p n is zero, or there is no difference found in @p n bytes.
 * @retval	A positive value if @p str1 is greater than @p str2.
 * @retval	A negative value if @p str1 is less than @p str2.
 */
int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	if (n == 0)
		return (0);
	while (*str1 && *str2 && *str1 == *str2 && --n > 0)
	{
		str1++;
		str2++;
	}
	return ((unsigned char)*str1 - (unsigned char)*str2);
}
