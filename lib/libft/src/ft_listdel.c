/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:45:19 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/09 14:00:01 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Delete the member variable `content` from @p `list` using @p `del`.
 *
 * @param[in,out]	list	Pointer of the node to be freed.
 * @param[in]		del		Function to delete the node.
 */
void	ft_listdelone(t_list *list, void (*del)(void *))
{
	if (list == NULL || del == NULL)
	{
		return ;
	}
	del(list->content);
	free(list);
}

/**
 * @brief Free the given node and all its successors.
 *
 * @param[in,out]	list	Pointer to the head pointer.
 * @param[in]		del		Function to delete each node in @p `list`.
 */
void	ft_listclear(t_list **list, void (*del)(void *))
{
	t_list	*node;
	t_list	*temp;

	if (list == NULL || *list == NULL)
	{
		return ;
	}
	node = *list;
	while (node)
	{
		temp = node->next;
		ft_listdelone(node, del);
		node = temp;
	}
	*list = NULL;
}
