/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:06:58 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/06 16:47:26 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	ft_count_words(char const *s, char c)
{
	size_t	words_counted;
	size_t	i;
	int		is_word;

	words_counted = 0;
	i = 0;
	is_word = 0;
	while (s[i])
	{
		if (is_word == 0 && s[i] != c)
		{
			words_counted++;
			is_word = 1;
		}
		if (s[i] == c)
			is_word = 0;
		i++;
	}
	return (words_counted);
}

static char	**ft_free_all(char **ptr, size_t i)
{
	while (ptr[i])
		free(ptr[i--]);
	free(ptr);
	return (NULL);
}

static size_t	ft_word_length(const char *s, char c)
{
	size_t	length;

	length = 0;
	while (s[length] && s[length] != c)
		length++;
	return (length);
}

static const char	*ft_skip_delimiters(const char *s, char c)
{
	while (*s == c)
		s++;
	return (s);
}

/**
 * @brief	Split the string @p str using character @p c as the delimiter.
 *
 * @param[in]	str	The string to split.
 * @param[in]	c	The delimiter character.
 *
 * @returns	An array of strings resulting from the split, or NULL on failure.
 *
 * @warning	The caller owns free() when done.
 */
char	**ft_split(char const *str, char c)
{
	char	**ptr;
	size_t	words_counted;
	size_t	word_length;
	size_t	i;

	i = 0;
	words_counted = ft_count_words(str, c);
	ptr = ft_calloc((words_counted + 1), sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	while (i < words_counted)
	{
		str = ft_skip_delimiters(str, c);
		word_length = ft_word_length(str, c);
		ptr[i] = ft_calloc(word_length + 1, sizeof(char));
		if (ptr[i] == NULL)
			return (ft_free_all(ptr, i));
		ft_memcpy(ptr[i], str, word_length);
		ptr[i++][word_length] = '\0';
		str += word_length;
	}
	return (ptr);
}
