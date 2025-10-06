/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_caseconvert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:46:55 by dbakker           #+#    #+#             */
/*   Updated: 2025/07/08 15:17:46 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Convert a letter from uppercase to lowercase.
 */
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	return (c);
}

/**
 * @brief Convert a letter from lowercase to uppercase.
 */
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c = c - 32;
	return (c);
}
