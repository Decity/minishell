/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:06:39 by ebelle            #+#    #+#             */
/*   Updated: 2025/09/18 11:19:28 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdbool.h>

static int	iswhitespace(int c)
{
	if ((c >= 9 && c <= 13) || (c == ' '))
		return (true);
	return (false);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	i = 0;
	while (iswhitespace(nptr[i]))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		num = (num * 10) + (nptr[i] - '0');
		i++;
	}
	return (num * sign);
}

// int	ft_atoi(const char *nptr)
// {
// 	int		i;
// 	long	num;
// 	int		sign;

// 	num = 0;
// 	sign = 1;
// 	i = 0;
// 	while (iswhitespace(nptr[i]))
// 		i++;
// 	if (nptr[i] == '+' || nptr[i] == '-')
// 	{
// 		if (nptr[i] == '-')
// 			sign = -1;
// 		i++;
// 	}
// 	while (ft_isdigit(nptr[i]))
// 	{
// 		if (num > (LONG_MAX - (nptr[i] - '0')) / 10)
// 		{
// 			if (sign == 1)
// 				return (-1);
// 			return (0);
// 		}
// 		num = (num * 10) + (nptr[i] - '0');
// 		i++;
// 	}
// 	return (num * sign);
// }

// void test(const char *str)
// {
// 	int result = ft_atoi(str);
// 	int comparison = atoi(str);
// 	if (result == comparison)
// 		printf("Pass: ");
// 	else
// 		printf("Fail: ");
// 	printf("atoi: [%d] ft_atoi: [%d]\n", comparison, result);
// }

// int main()
// {
// 	test("0");
// 	test("123");
// 	test("-123");
// 	test("+123");
// 	printf("\n");

// 	test("   123");
// 	test("   +123");
// 	test("   ++++123");
// 	test("   +++-123");
// 	test("   -+++123");
// 	test("   -123");
// 	test("   --123");
// 	test("   ---123");
// 	printf("\n");

// 	test("123abc");
// 	test("abc123");

// 	test(" ");
// 	test("	"); // tab
// 	test("");
// 	printf("\n");

// 	test("-2147483648");
// 	test("2147483647");
// 	test("-2147483649");
// 	test("2147483648");

// 	test("−2147483648"); // long min
// 	test("−2147483649"); // ^ - 1
// 	test("2147483648"); // long max
// 	test("2147483649"); // ^ + 1

// 	test("−9223372036854775807"); // long long min
// 	test("−9223372036854775817"); // ^ - 10
// 	test("9223372036854775807"); // long long max
// 	test("9223372036854775817"); // ^ + 10

// 	test("18446744073709551615"); // unsigned long long max (size_max)
// 	test("18446744073709551625"); // ^ + 10
// 	return (0);
// }