/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:20:32 by elie              #+#    #+#             */
/*   Updated: 2025/09/18 11:20:46 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static int	get_hexlen(unsigned long long int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 16;
		len++;
	}
	return (len);
}

int	get_hex(unsigned long long int n, const char *hex_set)
{
	char	*str;
	size_t	i;
	size_t	len;

	len = get_hexlen(n);
	i = len;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	else
	{
		while (n)
		{
			str[--i] = hex_set[n % 16];
			n /= 16;
		}
	}
	print_str(str);
	free(str);
	return (len);
}

int	print_hex(unsigned long long int n)
{
	return (get_hex(n, "0123456789abcdef"));
}

int	print_uhex(unsigned long long int n)
{
	return (get_hex(n, "0123456789ABCDEF"));
}
