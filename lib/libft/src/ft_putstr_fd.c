/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:07:41 by ebelle            #+#    #+#             */
/*   Updated: 2025/04/29 15:20:33 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

// int main()
// {
// 	char *null_str = NULL;
// 	char *null_str2 = ft_calloc(3, sizeof(char));
// 	ft_putstr_fd("123 abcDEF	!@#\n", 1);
// 	ft_putstr_fd("", 1);

// 	ft_putstr_fd(null_str, 1);
// 	ft_putstr_fd(null_str2, 1);
// 	free(null_str);
// 	free(null_str2);
// }