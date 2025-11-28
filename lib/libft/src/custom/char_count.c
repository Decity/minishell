/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:17:43 by dbakker           #+#    #+#             */
/*   Updated: 2025/11/27 17:17:52 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @return The amount of times @p `chr` appears in @p `str`.
 */
size_t	char_count(const char *str, int chr)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == chr)
		{
			count += 1;
		}
		i += 1;
	}
	return (count);
}
