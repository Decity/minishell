/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:07:06 by ebelle            #+#    #+#             */
/*   Updated: 2025/04/29 12:44:17 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>
#include <stdlib.h>

void	*ft_calloc(size_t n, size_t size)
{
	void	*array;

	if (size && n > SIZE_MAX / size)
		return (NULL);
	array = malloc(n * size);
	if (!array)
		return (NULL);
	ft_bzero(array, n * size);
	return (array);
}

// char	*test(unsigned int n)
// {
//     char *str;

// 	str = ft_calloc(n, sizeof(char));
// 	if (!str)
// 		return (free(str), NULL);
// 	return (str);
// }

// int main(void)
// {

// 	char *str = test(3);
// 	str[0] = '4';
// 	str[1] = '2';
// 	printf(str);
// 	printf("\n");

// }