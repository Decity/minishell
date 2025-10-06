/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:00:03 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/06 16:47:26 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Return the size of the linked list.
 *
 * @param[in]	list	Pointer to the head pointer.
 */
int	ft_lstsize(t_list *list)
{
	size_t	list_count;

	list_count = 0;
	while (list)
	{
		list_count++;
		list = list->next;
	}
	return (list_count);
}
