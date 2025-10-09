/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:17:04 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/09 12:47:54 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @return Pointer to the last node in @p `list`.
 */
t_list	*ft_listlast(t_list *list)
{
	if (list == NULL)
	{
		return (NULL);
	}
	while (list->next != NULL)
	{
		list = list->next;
	}
	return (list);
}

/**
 * @brief Return the second-to-last node in @p `list`.
 *
 * @param[in] list Pointer to the head of the list.
 *
 * @return Pointer to the second-to-last node, or `NULL` if @p `list` has
 * @return fewer than two nodes.
 */
t_list	*ft_listbefore_last(t_list *list)
{
	if (list == NULL)
	{
		return (NULL);
	}
	while (list->next && list->next->next)
	{
		list = list->next;
	}
	return (list);
}
