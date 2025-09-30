/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:08:07 by ebelle            #+#    #+#             */
/*   Updated: 2025/04/29 12:35:47 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
/*
int main()
{
    int n;
    char *tests[] = {"abc", "abd", "aba", "abc", "xyz", "", ""};
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);

    n = 3;
    for (size_t i = 0; i < num_tests - 1; i++)
    {
        printf("[%s] - [%s]\n", tests[i], tests[i+1]);
        printf("strncmp:	%i\n", strncmp(tests[i], tests[i+1], n));
        printf("ft_strncmp:	%i\n\n", ft_strncmp(tests[i], tests[i+1], n));
			
		if (strncmp(tests[i], tests[i+1], n) != ft_strncmp(tests[i],
		 tests[i+1], n))
			printf("\n\n###oopsie daisy\n\n");
	}
}
*/