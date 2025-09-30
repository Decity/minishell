/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:07:23 by ebelle            #+#    #+#             */
/*   Updated: 2025/04/29 12:25:11 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*ptr;

	ptr = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
			return ((void *)&ptr[i]);
		i++;
	}
	return (NULL);
}

// int	main()
// {
// 	char	str[] = "012345";

// 	printf("memchr:		%p\n", memchr(str, '3', 5));
// 	printf("ft_memchr:	%p\n", ft_memchr(str, '3', 5));

// 	printf("memchr:		%p\n", memchr(str, '4', 1));
// 	printf("ft_memchr:	%p\n", ft_memchr(str, '4', 1));

// }