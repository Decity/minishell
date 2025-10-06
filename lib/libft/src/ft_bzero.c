/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:38:21 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/06 17:25:25 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Write @p `num` bytes of zeros pointed to by @p `buffer`.
 *
 * @param[out]	buffer	Pointed area to fill.
 * @param[in]	num		Amount of zeros to write.
 */
void	ft_bzero(void *buffer, size_t num)
{
	ft_memset(buffer, 0, num);
}
