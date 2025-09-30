/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:07:11 by ebelle            #+#    #+#             */
/*   Updated: 2025/04/29 12:07:12 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (true);
	return (false);
}

// #include <stdio.h>
// int	main()
// {
// 	char tests[] = " 01abczABCZ	!@#$\n";
// 	for (int i = 0; tests[i]; i++)
// 	{
// 		if (ft_isalpha(tests[i]))
// 			printf("Pass: ");
// 		else
// 			printf("Fail: ");
// 		printf("%c\n", tests[i]);
// 	}
// }