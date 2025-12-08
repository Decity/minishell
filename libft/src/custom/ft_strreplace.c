/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:20:37 by elie              #+#    #+#             */
/*   Updated: 2025/10/09 16:17:05 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief this is where the logic of ft_strreplace is and where the actual replacing happens.
 */
static void	replace(char *result, const char *base_str, const char *pattern, const char *replacement)
{
	size_t			i;
	size_t			j;
	size_t			k;
	const size_t	len_base = ft_strlen(base_str);
	const size_t	len_pattern = ft_strlen(pattern);
	const size_t	len_replacement = ft_strlen(replacement);

	i = 0;
	j = 0;
	while (i < len_base)
	{
		if (i <= len_base - len_pattern && ft_strncmp(&base_str[i], pattern, len_pattern) == 0)
		{
			k = 0;
			while (k < len_replacement)
				result[j++] = replacement[k++];
			i += len_pattern;
		}
		else
			result[j++] = base_str[i++];
	}
	result[j] = '\0';
}

/**
 * @brief Returns a new string by replacing @p `pattern` in @p `base_str` with @p `replacement`
 *
 * @param base_str The base string in which replacements will occur
 * @param pattern The pattern that will be replaced
 * @param replacement The string that will replace the pattern
 */
char	*ft_strreplace(const char *base_str, const char *pattern, const char *replacement)
{
	const size_t	len_base = ft_strlen(base_str);
	const size_t	len_pattern = ft_strlen(pattern);
	const size_t	len_replacement = ft_strlen(replacement);
	char			*result;
	size_t			len_result;
	size_t			occurrences;

	if (!base_str || !pattern || !replacement)
		return (NULL);

	if (len_pattern == 0)
		return (ft_strdup(base_str));

	occurrences = ft_count_occurrences(base_str, pattern);
	if (len_replacement >= len_pattern)
		len_result = len_base + occurrences * (len_replacement - len_pattern);
	else
		len_result = len_base - occurrences * (len_pattern - len_replacement);

	result = ft_calloc(len_result + 1, sizeof(char));
	if (!result)
		return (NULL);

	replace(result, base_str, pattern, replacement);
	return (result);
}