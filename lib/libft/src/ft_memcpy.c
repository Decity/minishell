/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:07:27 by ebelle            #+#    #+#             */
/*   Updated: 2025/04/29 12:28:02 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

// int	main()
// {
// 	char dst[20];
// 	char src[] = "0123456789";

// 	char dst2[20];
// 	char src2[] = "0123456789";

// 	printf("memcpy:\n");
// 	printf("before: %s |", dst); 
// 	memcpy(dst, src, 5);
// 	printf("after: %s\n\n", dst);

// 	printf("ft_memcpy:\n");
// 	printf("before: %s |", dst2); 
// 	ft_memcpy(dst2, src2, 5);
// 	printf("after: %s\n\n", dst2);
// }