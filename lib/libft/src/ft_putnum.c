/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnum.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:05:49 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/07 12:15:33 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief Write @p num to the standard output.
 *
 * @param[in]	num	Signed 32-bit int to write.
 *
 * @return Length of the written number, or -1 on failure.
 */
int32_t	ft_putnum(int32_t num)
{
	int32_t	position;
	int32_t	writesize;
	char	array[INT32_LENGTH];
	bool	is_negative;

	position = INT32_LENGTH;
	is_negative = false;
	if (num < 0)
	{
		if (num == INT32_MIN)
			return (ft_putstr(S_INT32_MIN));
		ft_putchar('-');
		num = -num;
		is_negative = true;
	}
	if (num == 0)
		return (ft_putchar('0'));
	while (num != 0)
	{
		array[--position] = num % 10 + '0';
		num /= 10;
	}
	writesize = write(STDOUT_FILENO, &array[position], INT32_LENGTH - position);
	return (writesize + is_negative);
}

int32_t	ft_putunum(uint32_t num)
{
	char				array[INT32_LENGTH];
	int32_t				writesize;
	size_t				position;

	position = INT32_LENGTH;
	if (num == 0)
		return (ft_putchar('0'));
	while (num != 0)
	{
		array[--position] = DECIMAL[num % BASE_10];
		num /= BASE_10;
	}
	writesize = write(STDOUT_FILENO, &array[position], INT32_LENGTH - position);
	return (writesize);
}
