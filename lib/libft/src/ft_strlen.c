/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:55:06 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/07 15:02:39 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Return the strlen of the string @p s.
 */
size_t	ft_strlen(const char *str)
{
	size_t	strlen;

	strlen = 0;
	while (str[strlen])
	{
		strlen++;
	}
	return (strlen);
}

size_t	ft_strnlen(const char *str, size_t maxlen)
{
	size_t	strlen;

	strlen = 0;
	while (str[strlen] && strlen < maxlen)
	{
		strlen++;
	}
	return (strlen);
}
