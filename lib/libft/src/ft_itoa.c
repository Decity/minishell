/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:07:20 by ebelle            #+#    #+#             */
/*   Updated: 2025/04/29 13:18:21 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdlib.h>

static size_t	get_digits(int n)
{
	size_t	digits;

	digits = 1;
	if (n < 0)
		digits++;
	while (n >= 10 || n <= -10)
	{
		digits++;
		n /= 10;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	size_t	i;
	size_t	len;
	char	*str;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	len = get_digits(n);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		str[i] = '-';
		n *= -1;
		i++;
	}
	while (n >= 10)
	{
		str[len - 1] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	str[len - 1] = n + '0';
	return (str);
}

// int main(void)
// {
//     int test_cases[] = {0, 42, -42, 123456789, -123456789, INT_MAX, INT_MIN};

//     for (size_t i = 0; i < (sizeof(test_cases) / sizeof(test_cases[0])); i++)
//     {
//         int n = test_cases[i];
//         char *result = ft_itoa(n);
//         printf("ft_itoa(%d) = \"%s\"\n", n, result);
//         free(result);
//     }

// }