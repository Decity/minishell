/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:45:19 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/06 16:47:26 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Free the given node.
 *
 * @param[in,out]	list	Pointer of the node to be freed.
 * @param[in]		del		Used to free the content of the node.
 *
 * @note 	free() for @p del might be the callers preferred choice.
 */
void	ft_lstdelone(t_list *list, void (*del)(void *))
{
	if (list == NULL || del == NULL)
		return ;
	del(list->content);
	free(list);
}

/**
 * @brief	Free the given node and all its successors.
 *
 * On return, list is NULL.
 *
 * @param[in,out]	list	Pointer to the head pointer.
 * @param[in]		del		Frees each node in @p list.
 *
 * @note	free() for @p del might be the callers preferred choice.
 */
void	ft_lstclear(t_list **list, void (*del)(void *))
{
	t_list	*node;
	t_list	*temp;

	node = *list;
	if (list == NULL || *list == NULL)
		return ;
	while (node)
	{
		temp = node->next;
		ft_lstdelone(node, del);
		node = temp;
	}
	*list = NULL;
}
