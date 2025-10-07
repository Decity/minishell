/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:06:58 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/07 14:20:56 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	ft_count_words(char const *str, char delimiter)
{
	size_t	word_count;
	size_t	i;
	bool	is_word;

	word_count = 0;
	i = 0;
	is_word = 0;
	while (str[i])
	{
		if (is_word == false && str[i] != delimiter)
		{
			word_count++;
			is_word = true;
		}
		if (str[i] == delimiter)
			is_word = false;
		i++;
	}
	return (word_count);
}

static size_t	ft_word_length(const char *str, char delimiter)
{
	size_t	length;

	length = 0;
	while (str[length] && str[length] != delimiter)
		length++;
	return (length);
}

static const char	*ft_skip_delimiters(const char *str, char delimiter)
{
	while (*str == delimiter)
		str++;
	return (str);
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
char	**ft_split(char const *str, char delimiter)
{
	char	**ptr;
	size_t	words_counted;
	size_t	word_length;
	size_t	word;

	word = 0;
	words_counted = ft_count_words(str, delimiter);
	ptr = ft_calloc((words_counted + 1), sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	while (word < words_counted)
	{
		str = ft_skip_delimiters(str, delimiter);
		word_length = ft_word_length(str, delimiter);
		ptr[word] = ft_calloc(word_length + 1, sizeof(char));
		if (ptr[word] == NULL)
			return (ft_free2d((void **)ptr, word), NULL);
		ft_memcpy(ptr[word], str, word_length);
		ptr[word++][word_length] = '\0';
		str += word_length;
	}
	return (ptr);
}
