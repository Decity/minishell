/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:21:04 by elie              #+#    #+#             */
/*   Updated: 2025/09/18 11:21:05 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	pf_strlen(const char *s)
{
	size_t	i;

	if (!s || !s[0])
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	print_str(char *s)
{
	if (!s)
		return (write(1, "(null)", pf_strlen("(null)")));
	return (write(1, s, pf_strlen(s)));
}
