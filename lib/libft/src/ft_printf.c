/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:57:51 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/08 18:56:05 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int32_t	ft_conversions(char specifier, va_list args)
{
	int32_t	i;

	i = 1;
	if (specifier == 'c')
		i = ft_putchar(va_arg(args, int));
	else if (specifier == 's')
		i = ft_putstr(va_arg(args, char *));
	else if (specifier == 'p')
		i = ft_putptr(va_arg(args, uintptr_t));
	else if (specifier == 'i' || specifier == 'd')
		i = ft_putnum(va_arg(args, int32_t));
	else if (specifier == 'u')
		i = ft_putunum(va_arg(args, uint32_t));
	else if (specifier == 'x')
		i = ft_puthex_lower(va_arg(args, uint32_t));
	else if (specifier == 'X')
		i = ft_puthex_upper(va_arg(args, uint32_t));
	else if (specifier == '%')
		ft_putchar('%');
	return (i);
}

/**
 * @brief Print a simplified formatted string to the standard output.
 *
 * Unsupported formats are undefined behaviour.
 *
 * @param[in]	format	String to print to the standard output.
 * @param[in]	...		Formatted types to print.
 *
 * @return The length of the printed string, or -1 on failure.
 *
 * @note Supported format specifiers
 * @note | Specifier | Description                                        |
 * @note |-----------|----------------------------------------------------|
 * @note | `%d`/`%i` | Signed 32-bit integer                              |
 * @note | `%u`      | Unsigned 32-bit integer                            |
 * @note | `%x`      | Unsigned 32-bit integer (printed as lowercase hex) |
 * @note | `%X`      | Unsigned 32-bit integer (printed as uppercase hex) |
 * @note | `%c`      | Single character                                   |
 * @note | `%s`      | Null-terminated string                             |
 * @note | `%p`      | Pointer (printed as lowercase hex)                 |
 * @note | `%%`      | Literal percent sign (`%`)                         |
 */
int32_t	ft_printf(const char *format, ...)
{
	va_list	args;
	int32_t	string_length;
	int32_t	i;

	i = 0;
	string_length = 0;
	if (format == NULL)
		return (ft_putstr(format), -1);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
			string_length += ft_conversions(format[++i], args);
		else
		{
			ft_putchar(format[i]);
			string_length++;
		}
		i++;
	}
	va_end(args);
	return (string_length);
}
