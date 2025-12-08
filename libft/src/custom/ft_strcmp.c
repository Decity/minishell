/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 09:39:31 by elie              #+#    #+#             */
/*   Updated: 2025/11/04 09:39:34 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compare @p `str1` and @p `str2`.
 *
 * @param[in] str1	First string.
 * @param[in] str2	Second string.
 *
 * @retval 0 if @p `str1` == @p `str2`.
 * @retval A positive value if @p `str1` > @p `str2`.
 * @retval A negative value if @p `str1` < @p `str2`.
 */
int32_t	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
	{
		i++;
	}
	return ((uint8_t)str1[i] - (uint8_t)str2[i]);
}
