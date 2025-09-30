/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:07:13 by ebelle            #+#    #+#             */
/*   Updated: 2025/04/29 12:07:14 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (true);
	return (false);
}

// #include <stdio.h>
// #include <ctype.h>

// void	test(int c)
// {
// 	if (ft_isascii(c) && isascii(c))
// 		printf("Pass, is ascii: ");
// 	else if  (!ft_isascii(c) && !isascii(c))
// 		printf("Pass, not ascii: ");
// 	else
// 		printf("Fail: ");
// 	printf("%d\n", c);
// }

// int	main(void)
// {
// 	int array[] = {-1, 0, 1, 126, 127, 128, 300, -128};
// 	for (int i = 0; i < (int)(sizeof(array) / sizeof(array[0])); i++)
// 		test(array[i]);
// }