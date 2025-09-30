/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:07:43 by ebelle            #+#    #+#             */
/*   Updated: 2025/04/29 12:17:04 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_count_words(const char *str, char delimiter)
{
	size_t	word_count;
	size_t	i;

	word_count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == delimiter)
			i++;
		if (str[i])
		{
			word_count++;
			while (str[i] && str[i] != delimiter)
				i++;
		}
	}
	return (word_count);
}

static char	*ft_strndup(const char *s, size_t len)
{
	char	*sub_str;

	sub_str = ft_calloc(len + 1, sizeof(char));
	if (!sub_str)
		return (NULL);
	ft_memcpy(sub_str, s, len);
	sub_str[len] = '\0';
	return (sub_str);
}

static void	ft_free_n_strs(size_t n, char ***array)
{
	while (n--)
	{
		free((*array)[n]);
		(*array)[n] = NULL;
	}
	free(*array);
	*array = NULL;
}

static int	split(const char *s, char c, char **array, size_t word_count)
{
	size_t	start;
	size_t	end;
	size_t	i;

	start = 0;
	end = 0;
	i = 0;
	while (i < word_count)
	{
		while (s[start] && s[start] == c)
			start++;
		end = start;
		while (s[end] && s[end] != c)
			end++;
		array[i] = ft_strndup(&s[start], end - start);
		if (!array[i])
		{
			ft_free_n_strs(i, &array);
			return (0);
		}
		i++;
		start = end;
	}
	array[i] = NULL;
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char	**array;
	size_t	word_count;

	if (!s)
		return (NULL);
	word_count = ft_count_words(s, c);
	array = ft_calloc((word_count + 1), sizeof(char *));
	if (!array)
		return (NULL);
	if (!split(s, c, array, word_count))
		return (free(array), NULL);
	return (array);
}

// #include <stdio.h>

// int main(void)
// {
// 	char	**result;
// 	const char *test_cases[] = {
// 		"Hello world this is dog",
// 		"   Leading spaces",
// 		"Trailing spaces   ",
// 		"   Both leading and trailing spaces   ",
// 		"Spaces   between   words",
// 		"  Spaces   leading, between, and trailing    words   ",
// 		"HelloThisIsDog",
// 		"",
// 		"   ",
// 		NULL
// 	};

// 	for (size_t i = 0; test_cases[i]; i++)
// 	{
// 		printf("Test case %zu: \"%s\"\n", i + 1, test_cases[i]);
// 		result = ft_split(test_cases[i], ' ');
// 		if (!result)
// 			printf("Error: returned NULL\n");
// 		size_t j = 0;
// 		while (result[j])
// 		{
// 			printf("  Word %zu: %s\n", j + 1, result[j]);
// 			j++;
// 		}
// 		ft_free_n_strs(j, &result);
// 		printf("\n");
// 	}

// 	return (0);
// }