/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:08:02 by ebelle            #+#    #+#             */
/*   Updated: 2025/04/29 12:34:55 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

// #include <string.h>
// #include <stdio.h>
// int main()
// {
// 	char *tests[] = {"", "1", "22", "\n", "123456789", "\t	\t"};

// 	for (int i = 0; tests[i]; i++)
// 		printf("strlen: [%zu] ft_strlen: [%zu]\n", strlen(tests[i]),
//  ft_strlen(tests[i]));
// }