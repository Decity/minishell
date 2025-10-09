/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isthing2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:41:29 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/09 10:48:29 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @return `true` if @p `c` is a whitespace, `false` otherwise.
 */
bool	ft_isspace(int c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

/**
 * @return `true` if @p `c` is a lowercase character, `false` otherwise.
 */
bool	ft_islower(int c)
{
	return (c >= 'a' && c <= 'z');
}

/**
 * * @return `true` if @p `c` is an uppercase character, `false` otherwise.
 */
bool	ft_isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}
