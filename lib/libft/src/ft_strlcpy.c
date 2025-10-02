/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:08:00 by ebelle            #+#    #+#             */
/*   Updated: 2025/10/02 12:17:24 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copy `size` bytes from `src` to `dest`
 * 
 * dfghdfhgdfhdgfhdf
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	i = 0;
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (size > 0)
		dst[i] = '\0';
	return (src_len);
}

/*
int main(void)
{
    char dst1[20], dst2[20];
    const char *src = "123467890!";
    size_t size;

    strcpy(dst1, "abc");
    strcpy(dst2, "abc");
    size = 10;
    printf("just a regular ole test\n");
    printf("strlcpy:    %zu, Result: %s\n", strlcpy(dst1, src,
	 size), dst1);
    printf("ft_strlcpy: %zu, Result: %s\n\n", ft_strlcpy(dst2,
	 src, size), dst2);

    strcpy(dst1, "abc");
    strcpy(dst2, "abc");
    size = 5;
    printf("size too small\n");
    printf("strlcpy:    %zu, Result: %s\n", strlcpy(dst1, src,
	 size), dst1);
    printf("ft_strlcpy: %zu, Result: %s\n\n", ft_strlcpy(dst2,
	 src, size), dst2);

    strcpy(dst1, "abc");
    strcpy(dst2, "abc");
    size = 0;
    printf("size is 0\n");
    printf("strlcpy:    %zu, Result: %s\n", strlcpy(dst1, src,
	 size), dst1);
    printf("ft_strlcpy: %zu, Result: %s\n\n", ft_strlcpy(dst2,
	 src, size), dst2);

    return 0;
}
*/