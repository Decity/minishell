/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:09:29 by ebelle            #+#    #+#             */
/*   Updated: 2025/05/13 12:32:56 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*gnl_calloc(size_t n)
{
	char	*str;
	size_t	i;

	if (n && n > SIZE_MAX)
		return (NULL);
	str = malloc(n * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}

void	gnl_free_and_null(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

char	*gnl_strjoin(char *old_buffer, char *tmp)
{
	size_t	i;
	size_t	j;
	char	*new_buffer;

	if (!old_buffer)
		old_buffer = gnl_calloc(1);
	if (!old_buffer || !tmp)
		return (NULL);
	new_buffer = gnl_calloc(gnl_strlen(old_buffer) + gnl_strlen(tmp) + 1);
	if (!new_buffer)
		return (free(old_buffer), old_buffer = NULL);
	i = -1;
	j = -1;
	while (old_buffer[++i])
		new_buffer[i] = old_buffer[i];
	while (tmp[++j])
		new_buffer[i + j] = tmp[j];
	free(old_buffer);
	old_buffer = NULL;
	if (!new_buffer[0])
		gnl_free_and_null(&new_buffer);
	return (new_buffer);
}

char	*gnl_strndup(char *s, size_t n)
{
	char	*str;
	size_t	i;

	if (!s || !s[0])
		return (NULL);
	str = gnl_calloc(n + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}

char	*gnl_strchr(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}
