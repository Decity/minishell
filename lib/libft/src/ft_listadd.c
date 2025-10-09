/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:15:10 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/09 13:56:39 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Prepend @p `new` to @p `list`.
 *
 * @param[out]	list	List to prepend to.
 * @param[in]	new		Node to be prepended.
 */
void	ft_listadd_front(t_list **list, t_list *new)
{
	if (list == NULL || new == NULL)
	{
		return ;
	}
	new->next = *list;
	*list = new;
}

/**
 * @brief Append @p `new` to @p `list`.
 *
 * @param[out]	list	List to append to.
 * @param[in]	new		Node to be appended.
 */
void	ft_listadd_back(t_list **list, t_list *new)
{
	t_list	*node;

	node = *list;
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	while (node->next)
	{
		node = node->next;
	}
	node->next = new;
}
