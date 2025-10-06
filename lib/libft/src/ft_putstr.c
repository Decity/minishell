/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:33:28 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/06 16:51:04 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_int_to_hex(unsigned int hex, char *base)
{
	char	array[8];
	int		index;
	int		string_length;

	index = 0;
	while (hex != 0)
	{
		array[index++] = base[hex % 16];
		hex /= 16;
	}
	string_length = index;
	while (index--)
		write(1, &array[index], 1);
	return (string_length);
}

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	size_t	string_length;

	string_length = 0;
	if (str == NULL)
		return (write(1, "(null)", 6));
	return (write(1, str, ft_strlen(str)));
}

int	ft_puthex(unsigned int hex, char specifier)
{
	int				string_length;

	string_length = 1;
	if (hex == 0)
		return (write(1, "0", 1));
	if (specifier == 'x')
		string_length = ft_int_to_hex(hex, HEX_LOWER);
	else if (specifier == 'X')
		string_length = ft_int_to_hex(hex, HEX_UPPER);
	return (string_length);
}

int	ft_putptr(uintptr_t ptr)
{
	char		buffer[16];
	char		*base;
	size_t		index;
	int			string_length;

	index = 0;
	base = HEX_LOWER;
	if ((void *)ptr == NULL)
		return (write(1, "(nil)", 5));
	while (ptr)
	{
		buffer[index++] = base[ptr % 16];
		ptr /= 16;
	}
	string_length = (int)index;
	write(1, "0x", 2);
	while (index--)
		write(1, &buffer[index], 1);
	return (string_length + 2);
}
