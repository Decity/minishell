/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:08:15 by ebelle            #+#    #+#             */
/*   Updated: 2025/04/29 12:10:50 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	sub_str = ft_calloc(len + 1, sizeof(char));
	if (!sub_str)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		sub_str[i] = s[start + i];
		i++;
	}
	sub_str[i] = '\0';
	return (sub_str);
}

// int main(void)
// {
//     char *s = "0123456789ABCDEFGHIJKLNOP";
//     char *result;

//     result = ft_substr(s, 7, 5);
//     printf("start: 7, len: 5: %s\n", result);
//     free(result);

//     result = ft_substr(s, 20, 5);
//     printf("start: 20, len: 5: %s\n", result);
//     free(result);

//     result = ft_substr(s, 7, 50);
//     printf("start: 7, len: 50: %s\n", result);
//     free(result);

//     result = ft_substr("", 0, 5);
//     printf("start: 0, len: 5: %s\n", result);
//     free(result);

//     result = ft_substr(s, 7, 0);
//     printf("start: 7, len: 0: %s\n", result);
//     free(result);

//     return 0;
// }