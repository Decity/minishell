/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttype_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:11:35 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/09 11:02:52 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

/**
 * @brief Write @p `character` to @p `fd`.
 *
 * @param[in] character	Character to write.
 * @param[in] fd		Open file descriptor to write to.
 *
 * @return The size of @p `character` written.
 */
int32_t	ft_putchar_fd(char character, int fd)
{
	return (write(fd, &character, sizeof(char)));
}

/**
 * @brief Write @p `str` to @p `fd`.
 *
 * @param[in] str	String to write.
 * @param[in] fd	Open file descriptor to write to.
 *
 * @return The length of @p `str`, or `6` if @p `str` is `NULL`.
 */
int32_t	ft_putstr_fd(const char *str, int fd)
{
	static const char	null_str[] = "(null)";

	if (str == NULL)
	{
		return (write(STDOUT_FILENO, null_str, sizeof(null_str) - 1));
	}
	return (write(fd, str, ft_strlen(str)));
}

/**
 * @brief Write @p `str` with a newline to @p `fd`.
 *
 * @param[in] str	String to write.
 * @param[in] fd	Open file descriptor to write to.
 *
 * @return The length of @p `str`, or `6` if @p `str` is `NULL`.
 */
int32_t	ft_putendl_fd(const char *str, int fd)
{
	static const char	newline[] = "\n";
	size_t				strlen;

	strlen = ft_putstr_fd(str, fd);
	strlen += write(fd, newline, sizeof(newline) - 1);
	return (strlen);
}

/**
 * @brief Write @p `num` to @p `fd`.
 *
 * @param[in] num	Signed 32-bit integer to write.
 * @param[in] fd	Open file descriptor to write to.
 *
 * @return The length of @p `num`.
 */
int32_t	ft_putnum_fd(int32_t num, int fd)
{
	size_t	position;
	int32_t	write_size;
	char	array[INT32_LENGTH + 1];
	bool	is_negative;

	position = INT32_LENGTH;
	is_negative = false;
	if (num < 0)
	{
		if (num == INT32_MIN)
			return (ft_putstr_fd(S_INT32_MIN, fd));
		ft_putchar_fd('-', fd);
		num = -num;
		is_negative = true;
	}
	if (num == 0)
		return (ft_putchar_fd('0', fd));
	while (num != 0)
	{
		array[--position] = DECIMAL[num % BASE_10];
		num /= BASE_10;
	}
	array[INT32_LENGTH] = '\0';
	write_size = ft_putstr_fd(&array[position], fd);
	return (write_size + is_negative);
}
