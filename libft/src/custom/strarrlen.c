/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strarrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:14:54 by dbakker           #+#    #+#             */
/*   Updated: 2025/11/27 17:15:04 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @return The combined length of all strings in @p `strarr`.
 */
size_t	strarrlen(const char **strarr)
{
	size_t	length;
	size_t	i;
	size_t	j;

	length = 0;
	i = 0;
	j = 0;
	while (strarr[i])
	{
		while (strarr[i][j])
		{
			length += 1;
			j += 1;
		}
		j = 0;
		i += 1;
	}
	return (length);
}
