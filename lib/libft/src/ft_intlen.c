/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 22:13:09 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/06 22:16:56 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Count the amount of digits in @p `number`.
 *
 * @param[in] number The amount of digits to count.
 *
 * @return The length of @p `number`, including the sign character if negative.
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
