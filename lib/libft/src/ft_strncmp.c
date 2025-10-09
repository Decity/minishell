/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:33:33 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/09 11:04:04 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compare the first @p `num` bytes of @p `str1` and @p `str2`.
 *
 * @param[in] str1	First string.
 * @param[in] str2	Second string.
 * @param[in] num	Amount of characters to compare.
 *
 * @retval 0 if @p `str1` == @p `str2`, or @p `num` is 0.
 * @retval A positive value if @p `str1` > @p `str2`.
 * @retval A negative value if @p `str1` < @p `str2`.
 */
int32_t	ft_strncmp(const char *str1, const char *str2, size_t num)
{
	size_t	i;

	i = 0;
	if (num == 0)
	{
		return (0);
	}
	num--;
	while (str1[i] && str2[i] && str1[i] == str2[i] && i < num)
	{
		i++;
	}
	return ((uint8_t)str1[i] - (uint8_t)str2[i]);
}
