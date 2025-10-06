/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnum.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:05:49 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/06 22:37:13 by dbakker          ###   ########.fr       */
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
	static const char	s_int32_min[] = "-2147483648";
	int32_t				digit = 11;
	int32_t				write_size;
	char				array[11];
	bool				is_negative;

	if (num < 0)
	{
		if (num == INT32_MIN)
			return (write(STDOUT_FILENO, s_int32_min, sizeof(s_int32_min) - 1));
		ft_putchar('-');
		num = -num;
		is_negative = true;
	}
	if (num == 0)
		return (ft_putchar('0'));
	while (num != 0)
	{
		array[--digit] = num % 10 + '0';
		num /= 10;
	}
	write_size = write(STDOUT_FILENO, &array[digit], 11 - digit);
	return (write_size + is_negative);
}

int32_t	ft_putunum(uint32_t num)
{
	static const char	decimal[] = "0123456789";
	char				array[11];
	int32_t				write_size;
	size_t				position = 11;

	if (num == 0)
		return (ft_putchar('0'));
	while (num != 0)
	{
		array[--position] = decimal[num % 10];
		num /= 10;
	}
	write_size = write(STDOUT_FILENO, &array[position], 11 - position);
	return (write_size);
}
