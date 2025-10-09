/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_occurrence.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:20:40 by elie              #+#    #+#             */
/*   Updated: 2025/10/09 16:16:34 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief Counts  and returns how many time @p `pattern` occurs in @p `base_str`
 *
 * @return the amount of occurrences.
 */
size_t	ft_count_occurrences(const char *base_str, const char *pattern)
{
	size_t			count;
	size_t			i;
	const size_t	len_pattern = ft_strlen(pattern);
	const size_t	len_base = ft_strlen(pattern);

	count = 0;
	i = 0;
	while (i <= len_base - len_pattern)
	{
		if (ft_strncmp(&base_str[i], pattern, len_pattern) == 0)
		{
			count++;
			i += len_pattern;
		}
		else
			i++;
	}
	return (count);
}
