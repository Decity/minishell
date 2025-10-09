/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tocase.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:46:55 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/09 10:54:36 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @return The lowercase equivalent of @p `character`.
 */
int	ft_tolower(int character)
{
	if (ft_isupper(character))
	{
		character += 32;
	}
	return (character);
}

/**
 * @return The uppercase equivalent of @p `character`.
 */
int	ft_toupper(int character)
{
	if (ft_islower(character))
	{
		character -= 32;
	}
	return (character);
}
