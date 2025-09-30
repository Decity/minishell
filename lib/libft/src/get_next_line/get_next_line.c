/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:09:18 by ebelle            #+#    #+#             */
/*   Updated: 2025/05/13 12:33:03 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

size_t	gnl_strlen(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*read_to_buffer(int fd, char *buffer)
{
	char	*tmp;
	ssize_t	bytes_read;

	tmp = gnl_calloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (gnl_free_and_null(&buffer), NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !gnl_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read == -1)
			return (gnl_free_and_null(&tmp), free(buffer), NULL);
		if (bytes_read == 0)
			return (gnl_free_and_null(&tmp), buffer);
		tmp[bytes_read] = '\0';
		buffer = gnl_strjoin(buffer, tmp);
		if (!buffer)
			return (gnl_free_and_null(&tmp), NULL);
	}
	gnl_free_and_null(&tmp);
	return (buffer);
}

char	*get_line_from_buffer(char *buffer)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!buffer || !buffer[0])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = gnl_strndup(buffer, i);
	return (line);
}

char	*trim_buffer(char *buffer)
{
	size_t	i;
	char	*new_buffer;

	i = 0;
	if (!buffer ||!buffer[0])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	new_buffer = gnl_strndup(&buffer[i], gnl_strlen(&buffer[i]));
	gnl_free_and_null(&buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = read_to_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line_from_buffer(buffer);
	if (!line)
		return (gnl_free_and_null(&buffer), NULL);
	buffer = trim_buffer(buffer);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// int main() {
// 	const char *filename = "text.txt";

// 	int fd = open(filename, O_RDONLY);
// 	if (fd < 0) {
// 		printf("error: open()");
// 		return 1;
// 	}
// 	char* str = get_next_line(fd);

// 	while (str){
// 		printf("Result: %s", str);
// 		free(str);
// 		str = NULL;
// 		str = get_next_line(fd);
// 	}
// 	free(str);
// 	str = NULL;
// 	close(fd);
// 	return (0);
// }
