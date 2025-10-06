/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfunc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:39:14 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/06 16:47:26 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Apply a function to each node.
 *
 * @param[in,out]	list	Pointer to the head pointer.
 * @param[in]		func	Function to apply to each nodes content.
 */
void	ft_lstiter(t_list *list, void (*func)(void *))
{
	if (list == NULL || func == NULL)
		return ;
	while (list)
	{
		func(list->content);
		list = list->next;
	}
}

/**
 * @brief	Apply a function to each node.
 *
 * @param[in]	list	Pointer to the head pointer.
 * @param[in]	func	Function to apply to each nodes content.
 * @param[in]	del		Function to delete the list.
 *
 * @returns	Pointer to the head node with @p func applied to every node,
 * 			or NULL on Failure.
 *
 * @note	free() for @p del might be the callers preferred choice.
 */
t_list	*ft_lstmap(t_list *list, void *(*func)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*node;

	if (!list || !func || !del)
		return (NULL);
	new_list = NULL;
	while (list)
	{
		node = ft_lstnew(func(list->content));
		if (!node)
		{
			ft_lstclear(&node, *del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, node);
		list = list->next;
	}
	return (new_list);
}
