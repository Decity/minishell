/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:07:32 by ebelle            #+#    #+#             */
/*   Updated: 2025/04/29 12:27:37 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

// int main(void)
// {
// 		char str1[20] = "Hello, 42!";
//  	char str2[20] = "Hello, 42!";
// 	char empty1[5];
// 	char empty2[5];

//     memset(str1, 'A', 5);
//     ft_memset(str2, 'A', 5);
//     printf("memset:    %s\n", str1);
//     printf("ft_memset: %s\n\n", str2);

// 	// Undefined behaviour:
//     memset(empty1, 'B', 5);
//     ft_memset(empty2, 'B', 5);

//     printf("memset:    %s\n", empty1);
//     printf("ft_memset: %s\n", empty2);

// }
