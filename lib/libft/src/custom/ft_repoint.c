/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_repoint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:57:34 by elie              #+#    #+#             */
/*   Updated: 2025/10/09 16:16:55 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Frees @p `old_str` and assigns the pointer of @p `new_str`. Essentially replacing it.
 *
 * @param old_str pointer to a string that will be replaced.
 * @param new_str the new string that will usurp the throne.
 */
void	ft_repoint(char **old_str, char *new_str)
{
	if (!old_str)
		return ;
	if (*old_str)
		free(*old_str);
	*old_str = new_str;
}
