/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:08:05 by ebelle            #+#    #+#             */
/*   Updated: 2025/04/29 15:08:47 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s || !f)
		return (NULL);
	str = ft_calloc((ft_strlen(s) + 1), sizeof(char));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = f(i, (char)s[i]);
		i++;
	}
	return (str);
}

// char test(unsigned int i, char c)
// {
//     if (i % 2 == 0)
//         return (char)ft_toupper(c);
//     return (char)ft_tolower(c);
// }

// int main(void)
// {
//     char str[] = "abcdefghijlkmno";
//     char *result;

//     printf("before:		%s\n", str);
//     result = ft_strmapi(str, test);
//     printf("after:		%s\n", result);
// }
