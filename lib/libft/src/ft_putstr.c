/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:33:28 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/09 09:47:52 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief Write @p `character` to the standard output.
 *
 * @param[in] character Character to write.
 *
 * @return The size of @p `character` written.
 */
int32_t	ft_putchar(int character)
{
	return (write(STDOUT_FILENO, &character, sizeof(char)));
}

/**
 * @brief Write @p `str` to the standard output.
 *
 * @param[in] str String to write.
 *
 * @return The length of @p `str`, or `6` if @p `str` is `NULL`.
 */
int32_t	ft_putstr(const char *str)
{
	static const char	null_str[] = "(null)";

	if (str == NULL)
	{
		return (write(STDOUT_FILENO, null_str, sizeof(null_str) - 1));
	}
	return (write(STDOUT_FILENO, str, ft_strlen(str)));
}

/**
 * @brief Write @p `num` in its uppercase hexadecimal form to the standard
 * @brief output.
 *
 * @param[in] num Unsigned 32-bit integer to write in uppercase hexadecimal.
 *
 * @return The length of @p `num` its hexadecimal form.
 */
int32_t	ft_puthex_upper(uint32_t num)
{
	size_t	position;
	int32_t	write_size;
	char	array[HEX_LENGTH + 1];

	position = HEX_LENGTH;
	if (num == 0)
	{
		return (ft_putchar('0'));
	}
	while (num != 0)
	{
		array[--position] = HEX_UPPER[num % BASE_16];
		num /= BASE_16;
	}
	array[HEX_LENGTH] = '\0';
	write_size = ft_putstr(&array[position]);
	return (write_size);
}

/**
 * @brief Write @p `num` in its lowercase hexadecimal form to the standard
 * @brief output.
 *
 * @param[in] num Unsigned 32-bit integer to write in lowercase hexadecimal.
 *
 * @return The length of @p `num` its hexadecimal form.
 */
int32_t	ft_puthex_lower(uint32_t num)
{
	size_t	position;
	int32_t	write_size;
	char	array[HEX_LENGTH + 1];

	position = HEX_LENGTH;
	if (num == 0)
	{
		return (ft_putchar('0'));
	}
	while (num != 0)
	{
		array[--position] = HEX_LOWER[num % BASE_16];
		num /= BASE_16;
	}
	array[HEX_LENGTH] = '\0';
	write_size = ft_putstr(&array[position]);
	return (write_size);
}

/**
 * @brief Write the pointer address of @p num in standard output.
 *
 * The alpbabetical characters will be written in lowercase.
 *
 * @param[in] num Pointer address to write.
 *
 * @return Length of the pointer address.
 */
int32_t	ft_putptr(uintptr_t num)
{
	static const char	nil_str[] = "(nil)";
	size_t				position;
	int32_t				write_size;
	char				array[PTR_LENGTH + 1];

	position = PTR_LENGTH;
	if ((void *)num == NULL)
	{
		return (ft_putstr(nil_str));
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
	array[PTR_LENGTH] = '\0';
	write_size = ft_putstr(&array[position]);
	return (write_size);
}
