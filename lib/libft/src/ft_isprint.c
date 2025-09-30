/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:07:18 by ebelle            #+#    #+#             */
/*   Updated: 2025/04/29 12:07:19 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

int	ft_isprint(int c)
{
	if (c >= ' ' && c <= '~')
		return (true);
	return (false);
}

// #include <stdio.h>
// #include <ctype.h>

// void	test(int c)
// {
// 	if (ft_isprint(c) && isprint(c))
// 		printf("Pass, is print: ");
// 	else if  (!ft_isprint(c) && !isprint(c))
// 		printf("Pass, not print: ");
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