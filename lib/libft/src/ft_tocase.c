/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tocase.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:46:55 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/06 22:28:03 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Return the lowercase equivalent of @p `character`.
 *
 * @param[in] character An uppercase alphabetical character.
 *
 * @return The lowercase equivalent of @p `character`.
 */
int	ft_tolower(int character)
{
	if (character >= 'A' && character <= 'Z')
		character += 32;
	return (character);
}

/**
 * @brief Return the uppercase equivalent of @p `character`.
 *
 * @param[in] character A lowercase alphabetical character.
 *
 * @return The uppercase equivalent of @p `character`.
 */
int	ft_toupper(int character)
{
	if (character >= 'A' && character <= 'Z')
		character -= 32;
	return (character);
}
