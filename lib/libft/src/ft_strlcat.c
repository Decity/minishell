/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:07:58 by ebelle            #+#    #+#             */
/*   Updated: 2025/04/29 12:20:49 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = 0;
	src_len = 0;
	while (dst_len < size && dst[dst_len])
		dst_len++;
	while (src[src_len])
		src_len++;
	if (dst_len == size)
		return (size + src_len);
	i = 0;
	while ((dst_len + i + 1) < size && src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	if (dst_len + i < size)
		dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

// int main()
// {
//     char dst1[20], dst2[20];
//     const char *src = "123";
//     size_t size;

//     strcpy(dst1, "abc");
//     strcpy(dst2, "abc");
//     size = 10;
//     printf("Normal concatenation\n");
//     printf("strlcat:    %zu, Result: %s\n", strlcat(dst1, src, 
// size), dst1);
//     printf("ft_strlcat: %zu, Result: %s\n\n", ft_strlcat(dst2, 
// src, size), dst2);

//     strcpy(dst1, "abc");
//     strcpy(dst2, "abc");
//     size = 5;
//     printf("Size too small\n");
//     printf("strlcat:    %zu, Result: %s\n", strlcat(dst1, src, 
// size), dst1);
//     printf("ft_strlcat: %zu, Result: %s\n\n", ft_strlcat(dst2, 
// src, size), dst2);

//     strcpy(dst1, "abc");
//     strcpy(dst2, "abc");
//     size = 0;
//     printf("Size is 0\n");
//     printf("strlcat:    %zu, Result: %s\n", strlcat(dst1, src, 
// size), dst1);
//     printf("ft_strlcat: %zu, Result: %s\n\n", ft_strlcat(dst2, 
// src, size), dst2);

//     strcpy(dst1, "abc");
//     strcpy(dst2, "abc");
//     size = 2;
//     printf("Size is smaller than dst\n");
//     printf("strlcat:    %zu, Result: %s\n", strlcat(dst1, src, 
// size), dst1);
//     printf("ft_strlcat: %zu, Result: %s\n\n", ft_strlcat(dst2, 
// src, size), dst2);

//     strcpy(dst1, "abc");
//     strcpy(dst2, "abc");
//     src = "";
//     size = 10;
//     printf("Src is empty\n");
//     printf("strlcat:    %zu, Result: %s\n", strlcat(dst1, src, 
// size), dst1);
//     printf("ft_strlcat: %zu, Result: %s\n\n", ft_strlcat(dst2, 
// src, size), dst2);

//     strcpy(dst1, "");
//     strcpy(dst2, "");
//     src = "DEF";
//     size = 10;
//     printf("Dst is empty\n");
//     printf("strlcat:    %zu, Result: %s\n", strlcat(dst1, src, 
// size), dst1);
//     printf("ft_strlcat: %zu, Result: %s\n\n", ft_strlcat(dst2, 
// src, size), dst2);

//     strcpy(dst1, "");
//     strcpy(dst2, "");
//     src = "";
//     size = 10;
//     printf("both are empty\n");
//     printf("strlcat:    %zu, Result: %s\n", strlcat(dst1, src, 
// size), dst1);
//     printf("ft_strlcat: %zu, Result: %s\n\n", ft_strlcat(dst2, 
// src, size), dst2);

//     return 0;
// }