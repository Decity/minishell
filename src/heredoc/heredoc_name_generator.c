/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_name_generator.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 12:49:04 by dbakker           #+#    #+#             */
/*   Updated: 2025/11/28 09:44:33 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Generate a pointer of length @p `size` read from `/dev/urandom`.
 *
 * The returning pointer can contain zero bytes, therefore it
 * should not be treated as a null-terminated string.
 *
 * @param[in] size Length of the pointer.
 *
 * @return A string of characters, or `NULL` on failure.
 *
 * @warning Caller owns free().
 */
void	*generate_random_pointer(size_t size)
{
	const char	filepath[] = "/dev/urandom";
	int			fd;
	void		*ptr;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
	{
		return (NULL);
	}
	ptr = ft_calloc(size, sizeof(char));
	if (ptr == NULL)
	{
		return (NULL);
	}
	if (read(fd, ptr, size) == -1)
	{
		free(ptr);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (ptr);
}

/**
 * @brief Convert @p `size` bytes of @p `ptr` into a string of hexadecimal
 * @brief characters.
 *
 * Returns `NULL` if @p `ptr` is `NULL`.
 *
 * @param[in] ptr	Pointer to convert to a string of base 16 characters.
 * @param[in] size	Amount of bytes to copy.
 *
 * @return Pointer to the newly allocated string, or `NULL` on failure.
 *
 * @warning Caller owns free().
 */
char	*convert_mem_to_base16(const void *ptr, size_t size)
{
	size_t	i;
	char	*hex_str;

	if (ptr == NULL)
	{
		return (NULL);
	}
	hex_str = ft_calloc(size + 1, sizeof(char));
	if (hex_str == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		hex_str[i] = HEX_LOWER[((uint8_t *)ptr)[i] % BASE_16];
		i++;
	}
	return (hex_str);
}

/**
 * @return A randomly generated string of base 16 characters, or `NULL`
 * @return on failure.
 *
 * The length of the string is defined by `HEREDOC_FILENAME_LENGTH`.
 *
 * @warning Caller owns free().
 */
char	*generate_heredoc_name(void)
{
	const char	path[] = "/tmp/";
	char		*filename;
	char		*retstr;
	void		*ptr;

	ptr = generate_random_pointer(HEREDOC_FILENAME_LENGTH);
	filename = convert_mem_to_base16(ptr, HEREDOC_FILENAME_LENGTH);
	retstr = ft_strjoin(path, filename);
	free(filename);
	free(ptr);
	return (retstr);
}
