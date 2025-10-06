/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnum.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:05:49 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/06 16:51:04 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_less_than_zero(int nbr)
{
	if (nbr < 0)
	{
		write(1, "-", 1);
		return (1);
	}
	return (0);
}

static int	ft_is_zero(int nbr)
{
	if (nbr == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	return (0);
}

static int	ft_length_of_num(long n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	ft_putnbr(int num)
{
	int		array[11];
	int		index;
	int		int_length;
	long	lnum;

	index = 0;
	lnum = num;
	int_length = ft_length_of_num(lnum);
	if (ft_is_zero(lnum))
		return (int_length);
	if (ft_less_than_zero(lnum))
		lnum = -lnum;
	while (lnum != 0)
	{
		array[index++] = lnum % 10 + '0';
		lnum /= 10;
	}
	while (index--)
		write(1, &array[index], 1);
	return (int_length);
}

int	ft_putunbr(unsigned int num)
{
	int	array[11];
	int	index;
	int	string_length;

	index = 0;
	string_length = ft_length_of_num(num);
	if (ft_is_zero(num))
		return (string_length);
	while (num > 0)
	{
		array[index++] = num % 10 + '0';
		num /= 10;
	}
	while (index--)
		write(1, &array[index], 1);
	return (string_length);
}
