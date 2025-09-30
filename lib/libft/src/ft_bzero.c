/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:07:03 by ebelle            #+#    #+#             */
/*   Updated: 2025/04/29 12:07:04 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

// int main()
// {
// 	char str1[] = "0123456";
// 	char str2[] = "0123456";

// 	printf("bzero\nBefore: %s", str1);
// 	bzero(&str1[3], 3);
// 	printf(" | After: %s\n\n", str1);

// 	printf("ft_bzero\nBefore: %s", str2);
// 	ft_bzero(&str2[3], 3);
// 	printf(" | After: %s\n\n", str2);

// }