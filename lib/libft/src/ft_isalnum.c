/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:07:08 by ebelle            #+#    #+#             */
/*   Updated: 2025/04/29 12:22:42 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'))
		return (true);
	return (false);
}

// #include <stdio.h>
// int	main()
// {
// 	char tests[] = " 013abczABCZ	!@#$\n";
// 	for (int i = 0; tests[i]; i++)
// 	{
// 		if (ft_isalnum(tests[i]))
// 			printf("Pass: ");
// 		else
// 			printf("Fail: ");
// 		printf("%c\n", tests[i]);
// 	}
// }