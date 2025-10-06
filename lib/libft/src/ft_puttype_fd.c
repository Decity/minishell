/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttype_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:11:35 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/06 16:47:26 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Writes character @p c to the specified file descriptor @p fd
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/**
 * @brief	Writes string @p str to the specified file descriptor @p fd
 */
void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

/**
 * @brief	Writes string @p str with a newline to the specified file descriptor
 * 			@p fd
 */
void	ft_putendl_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

/**
 * @brief Writes integer @p num to the specified file descriptor @p fd
 */
void	ft_putnbr_fd(int num, int fd)
{
	if (num == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (num < 0)
	{
		write(fd, "-", 1);
		num = -num;
	}
	if (num >= 10)
		ft_putnbr_fd(num / 10, fd);
	num = num % 10 + '0';
	write(fd, &num, 1);
}
