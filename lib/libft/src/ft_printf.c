/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:57:51 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/06 16:51:04 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_conversions(char specifier, va_list args)
{
	int	i;

	i = 1;
	if (specifier == 'c')
		i = ft_putchar((char)va_arg(args, int));
	else if (specifier == 's')
		i = ft_putstr((char *)va_arg(args, char *));
	else if (specifier == 'p')
		i = ft_putptr((uintptr_t)va_arg(args, uintptr_t));
	else if (specifier == 'i' || specifier == 'd')
		i = ft_putnbr((int)va_arg(args, int));
	else if (specifier == 'u')
		i = ft_putunbr((unsigned int)va_arg(args, unsigned int));
	else if (specifier == 'x' || specifier == 'X')
		i = ft_puthex((unsigned int)va_arg(args, unsigned int), specifier);
	else if (specifier == '%')
		write(1, "%", 1);
	return (i);
}

/*
- Print format
*/
int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		string_length;
	int		i;

	i = 0;
	string_length = 0;
	if (format == NULL)
		return (-1);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
			string_length += ft_conversions(format[++i], args);
		else
		{
			write(1, &format[i], 1);
			string_length++;
		}
		i++;
	}
	va_end(args);
	return (string_length);
}
