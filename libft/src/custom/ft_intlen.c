/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 22:13:09 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/08 16:58:59 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Count the amount of digits in @p `number`.
 *
 * This includes the negative sign character.
 *
 * @param[in] number The number to count the digits.
 *
 * @return The length of @p `number`.
 */
size_t	ft_intlen(int32_t number)
{
	size_t	lenght;

	lenght = 0;
	if (number == 0)
	{
		return (1);
	}
	if (number < 0)
	{
		lenght++;
	}
	while (number != 0)
	{
		number /= 10;
		lenght++;
	}
	return (lenght);
}
