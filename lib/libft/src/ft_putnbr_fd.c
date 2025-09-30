/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:07:39 by ebelle            #+#    #+#             */
/*   Updated: 2025/04/29 12:34:21 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	char	num;

	if (n == INT_MIN)
		return (ft_putstr_fd("-2147483648", fd));
	if (n < 0)
	{
		n *= -1;
		ft_putchar_fd('-', fd);
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	num = (n % 10) + '0';
	write(fd, &num, 1);
}

// int main()
// {
// 	int	tests[] = {-1, 0, 1, INT_MIN, INT_MAX};
// 	for (unsigned long i = 0; i < (sizeof(tests) / sizeof(int)); i++)
// 	{
// 		ft_putnbr_fd(tests[i], 1);
// 		printf("\n");
// 	}
// }