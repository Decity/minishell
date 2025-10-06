/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:17:04 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/06 16:47:26 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Return the pointer to the last node in @p list.
 */
t_list	*ft_lstlast(t_list *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

/**
 * @brief	Return the second-to-last node in a singly linked list.
 *
 * @param[in]	list	Pointer to the head of the list.
 *
 * @returns	Pointer to the second-to-last node,
 * 			or NULL if list has fewer than two nodes.
 */
t_list	*ft_lstbefore_last(t_list *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next && list->next->next)
		list = list->next;
	return (list);
}
