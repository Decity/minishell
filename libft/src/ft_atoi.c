/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:52:08 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/08 16:56:46 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Convert @p `str` to a signed 32-bit integer.
 *
 * @param[in] str The String to convert.
 *
 * @return The converted value.
 */
int32_t	ft_atoi(const char *str)
{
	int32_t	number;
	int32_t	i;
	int8_t	sign;

	number = 0;
	i = 0;
	sign = 1;
	while (ft_isspace(str[i]))
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
		{
			sign = -sign;
		}
	}
	while (ft_isdigit(str[i]))
	{
		number = number * 10 + (str[i++] - '0');
	}
	return (number * sign);
}
