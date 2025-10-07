/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttype_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:11:35 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/07 12:25:01 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
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
	static const char	newline[] = "\n";

	write(fd, str, ft_strlen(str));
	write(fd, newline, sizeof(newline) - 1);
}

/**
 * @brief Writes integer @p num to the specified file descriptor @p fd
 */
void	ft_putnum_fd(int32_t num, int fd)
{
	int32_t				digit;
	char				array[INT32_LENGTH];
	bool				is_negative;

	digit = INT32_LENGTH;
	is_negative = false;
	if (num < 0)
	{
		if (num == INT32_MIN)
		{
			ft_putstr_fd(S_INT32_MIN, fd);
			return ;
		}
		ft_putchar('-');
		num = -num;
		is_negative = true;
	}
	if (num == 0)
		ft_putchar('0');
	while (num != 0)
	{
		array[--digit] = num % BASE_10 + '0';
		num /= BASE_10;
	}
}
