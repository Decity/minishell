/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:33:28 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/06 22:41:32 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_int_to_hex(unsigned int hex, char *base)
{
	char	array[8];
	int		i;
	int		string_length;

	i = 0;
	while (hex != 0)
	{
		array[i++] = base[hex % 16];
		hex /= 16;
	}
	string_length = i;
	while (i--)
		write(1, &array[i], 1);
	return (string_length);
}

int	ft_putchar(int character)
{
	return (write(STDOUT_FILENO, &character, 1));
}

int	ft_putstr(char *str)
{
	if (str == NULL)
		return (write(STDOUT_FILENO, "(null)", 6));
	return (write(STDOUT_FILENO, str, ft_strlen(str)));
}

int	ft_puthex(unsigned int hex, char specifier)
{
	int32_t	string_length;

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
	size_t		i;
	int			string_length;

	i = 0;
	base = HEX_LOWER;
	if ((void *)ptr == NULL)
		return (write(1, "(nil)", 5));
	while (ptr)
	{
		buffer[i++] = base[ptr % 16];
		ptr /= 16;
	}
	string_length = (int)i;
	write(1, "0x", 2);
	while (i--)
		write(1, &buffer[i], 1);
	return (string_length + 2);
}
