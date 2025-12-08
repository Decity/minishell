/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listfunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:39:14 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/09 14:00:16 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Apply @p `func` to each node.
 *
 * @param[in,out]	list Pointer to the head pointer.
 * @param[in]		func Function to apply to each nodes content.
 */
void	ft_listiter(t_list *list, void (*func)(void *))
{
	if (list == NULL || func == NULL)
	{
		return ;
	}
	while (list)
	{
		func(list->content);
		list = list->next;
	}
}

/**
 * @brief Create a new list from @p `list` and apply @p `func` to each newly
 * @brief created member variable `content`.
 *
 * @param[in] list	Pointer to the head pointer.
 * @param[in] func	Function to apply to each nodes content.
 * @param[in] del	Function to delete the list.
 *
 * @return Pointer to the head node with @p `func` applied to every node,
 * @return or `NULL` on Failure.
 */
t_list	*ft_listmap(t_list *list, void *(*func)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*node;

	if (list == NULL || func == NULL || del == NULL)
	{
		return (NULL);
	}
	new_list = NULL;
	while (list)
	{
		node = ft_listnew(func(list->content));
		if (node == NULL)
		{
			ft_listclear(&node, *del);
			return (NULL);
		}
		ft_listadd_back(&new_list, node);
		list = list->next;
	}
	return (new_list);
}
