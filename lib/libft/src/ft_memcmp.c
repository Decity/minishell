/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:07:25 by ebelle            #+#    #+#             */
/*   Updated: 2025/04/29 12:26:26 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*ptr_s1;
	const unsigned char	*ptr_s2;

	ptr_s1 = (const unsigned char *)s1;
	ptr_s2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (ptr_s1[i] != ptr_s2[i])
			return (ptr_s1[i] - ptr_s2[i]);
		i++;
	}
	return (0);
}

// int main()
// {
//     int n;
//     char *tests[] = {"abc", "abd", "aba", "abc", "xyz", "", ""};
//     size_t num_tests = sizeof(tests) / sizeof(tests[0]);

//     n = 3;
//     for (size_t i = 0; i < num_tests - 1; i++)
//     {
//         printf("[%s] - [%s]\n", tests[i], tests[i+1]);
//         printf("memcmp:		%i\n", memcmp(tests[i], tests[i+1], n));
//         printf("ft_memcmp:	%i\n\n", ft_memcmp(tests[i], tests[i+1], n));

// 		if (memcmp(tests[i], tests[i+1], n) != ft_memcmp(tests[i], tests[i+1]
// , n))
// 			printf("\n\n###oopsie daisy\n\n");
// 	}
// }