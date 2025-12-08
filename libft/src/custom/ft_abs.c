/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:42:01 by dbakker           #+#    #+#             */
/*   Updated: 2025/11/13 13:52:58 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @return The absolute value of @p `number`, meaning a positive number.
 *
 * @warning `INT_MIN` is undefined behaviour.
 */
int32_t	ft_abs(int32_t number)
{
	if (number < 0)
	{
		return (-number);
	}
	return (number);
}
