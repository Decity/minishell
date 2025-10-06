/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:48:29 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/06 16:50:48 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strjoin_gnl(char *buffer, char *line, ssize_t fd_bytes_read)
{
	char	*new_str;
	ssize_t	i;
	ssize_t	j;

	i = 0;
	j = 0;
	if (!buffer)
		buffer = ft_calloc(1, sizeof(char));
	if (!buffer || !line)
		return (NULL);
	new_str = ft_calloc(ft_strlen(buffer) + ft_strlen(line) \
+ 1, sizeof(char));
	if (!new_str)
		return (free(buffer), NULL);
	while (buffer[j])
		new_str[i++] = buffer[j++];
	j = 0;
	while (line[j] && j < fd_bytes_read)
		new_str[i++] = line[j++];
	free(buffer);
	return (new_str);
}

static char	*get_returning_line(char *buffer)
{
	char	*line;
	size_t	i;

	i = 0;
	if (buffer[i] == '\0')
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i] = buffer[i];
	return (line);
}

static char	*trim_leftover_line(char *buffer)
{
	char	*leftover_line;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
		return (free(buffer), NULL);
	leftover_line = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	if (!leftover_line)
		return (free(buffer), NULL);
	i++;
	while (buffer[i])
		leftover_line[j++] = buffer[i++];
	free(buffer);
	return (leftover_line);
}

static char	*fill_buffer(char *buffer, int fd)
{
	ssize_t	fd_bytes_read;
	char	*line;

	fd_bytes_read = 1;
	line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!line)
		return (NULL);
	while (ft_strchr(buffer, '\n') == NULL)
	{
		fd_bytes_read = read(fd, line, BUFFER_SIZE);
		if (fd_bytes_read == 0)
			break ;
		if (fd_bytes_read == -1)
			return (free(line), free(buffer), NULL);
		buffer = ft_strjoin_gnl(buffer, line, fd_bytes_read);
	}
	free(line);
	return (buffer);
}

/**
 * @brief	Return a line from the specified file descriptor @p fd
 *
 * Every subsequent function call will return the next line.
 *
 * @param[in]	fd File descriptor to read from.
 *
 *
 */
char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD];
	char		*line;

	if (BUFFER_SIZE == 0 || fd < 0)
		return (NULL);
	buffer[fd] = fill_buffer(buffer[fd], fd);
	if (!buffer[fd])
		return (NULL);
	line = get_returning_line(buffer[fd]);
	buffer[fd] = trim_leftover_line(buffer[fd]);
	return (line);
}
