/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:07:30 by ebelle            #+#    #+#             */
/*   Updated: 2025/04/29 12:36:52 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	if (dest < src)
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
			i++;
		}
	}
	else
		while (n--)
			((unsigned char *)dest)[n] = ((const unsigned char *)src)[n];
	return (dest);
}

/*
int main(void)
{
	char src1[] = "Hello, world!";
	char dest1[20];
	char src2[] = "Hello, world!";
	char dest2[20];

	ft_memmove(dest1, src1, 13);
	memmove(dest2, src2, 13);
	printf("ft_memmove: %s\n", dest1);
	printf("memmove:    %s\n\n", dest2);

	char overlap1[] = "123456789";
	char overlap2[] = "123456789";
	printf("src < dest:\n");
	ft_memmove(overlap1 + 3, overlap1, 5);
	memmove(overlap2 + 3, overlap2, 5);
	printf("ft_memmove: %s\n", overlap1);
	printf("memmove:    %s\n\n", overlap2);

	char overlap3[] = "123456789";
	char overlap4[] = "123456789";
	printf("dest < src:\n");
	ft_memmove(overlap3, overlap3 + 3, 5);
	memmove(overlap4, overlap4 + 3, 5);
	printf("ft_memmove: %s\n", overlap3);
	printf("memmove:    %s\n\n", overlap4);

	char zero1[] = "123456789";
	char zero2[] = "123456789";
	printf("0: \n");
	ft_memmove(zero1, zero1 + 3, 0);
	memmove(zero2, zero2 + 3, 0);
	printf("ft_memmove: %s\n", zero1);
	printf("memmove:    %s\n\n", zero2);
}
	*/