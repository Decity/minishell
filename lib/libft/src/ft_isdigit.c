/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:07:15 by ebelle            #+#    #+#             */
/*   Updated: 2025/04/29 12:07:16 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

// #include <stdio.h>
// #include <ctype.h>

// void	test(int c)
// {
// 	if (ft_isdigit(c) && isdigit(c))
// 		printf("Pass, is digit: ");
// 	else if  (!ft_isdigit(c) && !isdigit(c))
// 		printf("Pass, not digit: ");
// 	else
// 		printf("Fail: ");
// 	printf("%c\n", c);
// }

// int	main(void)
// {
// 	char array[] = " 1234abczABCZ	!@#$ \n'";
// 	for (int i = 0; i < (int)(sizeof(array) / sizeof(array[0])); i++)
// 		test(array[i]);
// }