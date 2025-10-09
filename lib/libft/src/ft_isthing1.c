/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isthing1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:41:29 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/09 14:26:55 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @return `true` if @p `c` is alphabetic, `false` otherwise.
 */
bool	ft_isalpha(int c)
{
	return (ft_islower(c) || ft_isupper(c));
}

/**
 * @return `true` if @p `c` is standard ASCII, `false` otherwise.
 */
bool	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

/**
 * @return `true` if @p `c` is a digit, `false` otherwise.
 */
bool	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/**
 * @return `true` if @p `c` is a printable character, `false` otherwise.
 */
bool	ft_isprint(int c)
{
	return (c >= ' ' && c <= '~');
}

/**
 * @return `true` if @p `c` is alphanumeric, `false` otherwise.
 */
bool	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
