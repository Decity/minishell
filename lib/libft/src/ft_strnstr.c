/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:08:10 by ebelle            #+#    #+#             */
/*   Updated: 2025/04/29 12:17:26 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	little_len = ft_strlen(little);
	if (little_len == 0)
		return ((char *)big);
	if (len == 0 || !big[0])
		return (NULL);
	i = 0;
	while (i < len && big[i])
	{
		j = 0;
		while (i + j < len && big[i + j] == little[j])
		{
			j++;
			if (j == little_len)
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}

// int main()
// {
//     const char big[] = "abab EDFEF 12    !@";
//     const char *little;
//     size_t len = 20;

//     little = "EF";
//     printf("Searching for %s\n", little);
//     printf("ft_strnstr: %s\n\n", ft_strnstr(big, little, len));

//     little = "ab";
//     printf("Searching for %s\n", little);
//     printf("ft_strnstr: %s\n\n", ft_strnstr(big, little, len));

//     little = "!@";
//     printf("Searching for %s\n", little);
//     printf("ft_strnstr: %s\n\n", ft_strnstr(big, little, len));

//     little = "42";
//     printf("Searching for %s\n", little);
//     printf("ft_strnstr: %s\n\n", ft_strnstr(big, little, len));

//     little = "";
//     printf("Searching for %s\n", little);
//     printf("ft_strnstr: %s\n\n", ft_strnstr(big, little, len));

//     const char empty_big[] = "";
//     little = "ab";
//     printf("Searching for %s\n", little);
//     printf("ft_strnstr: %s\n\n", ft_strnstr(empty_big, little, len));
// }