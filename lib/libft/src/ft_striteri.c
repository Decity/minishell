/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:07:54 by ebelle            #+#    #+#             */
/*   Updated: 2025/04/29 12:34:41 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// void test(unsigned int i, char *c)
// {
//     if (i % 2 == 0)
//         *c = (char)ft_toupper(*c);
//     else
//         *c = (char)ft_tolower(*c);
// }

// int main(void)
// {
//     char str[] = "abcDEFhijKLMNOpqrstuVWXYZ";

//     printf("before:		%s\n", str);
//     ft_striteri(str, test);
//     printf("after:		%s\n", str);
// }
