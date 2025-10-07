/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:33:28 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/07 12:11:08 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int32_t	ft_int_to_hex(uint32_t hex, char *base)
{
	size_t	i;
	int32_t	string_length;
	char	array[8];

	i = 0;
	while (hex != 0)
	{
		array[i++] = base[hex % BASE_16];
		hex /= BASE_16;
	}
	string_length = i;
	while (i--)
		write(STDOUT_FILENO, &array[i], 1);
	return (string_length);
}

int32_t	ft_putchar(int character)
{
	return (write(STDOUT_FILENO, &character, 1));
}

int32_t	ft_putstr(const char *str)
{
	static const char	null_str[] = "(null)";

	if (str == NULL)
		return (write(STDOUT_FILENO, null_str, sizeof(null_str) - 1));
	return (write(STDOUT_FILENO, str, ft_strlen(str)));
}

int32_t	ft_puthex(uint32_t hex, char specifier)
{
	int32_t	string_length;

	string_length = 1;
	if (hex == 0)
		return (ft_putchar('0'));
	if (specifier == 'x')
		string_length = ft_int_to_hex(hex, HEX_LOWER);
	else if (specifier == 'X')
		string_length = ft_int_to_hex(hex, HEX_UPPER);
	return (string_length);
}

/**
 * @brief Write the pointer address of @p num in standard output.
 *
 * The alpbabetical characters will be written in lowercase.
 *
 * @param[in]	num	Pointer address to write.
 *
 * @return Length of the written number, or -1 on failure.
 */
int32_t	ft_putptr(uintptr_t num)
{
	int32_t	write_size;
	size_t	position;
	char	array[PTR_LENGTH];

	position = PTR_LENGTH;
	if ((void *)num == NULL)
	{
		return (ft_putstr("(nil)"));
	}
	if (num == 0)
	{
		return (ft_putchar('0'));
	}
	while (num != 0)
	{
		array[--position] = HEX_LOWER[num % BASE_16];
		num /= BASE_16;
	}
	array[--position] = 'x';
	array[--position] = '0';
	write_size = write(STDOUT_FILENO, &array[position], PTR_LENGTH - position);
	return (write_size);
}
