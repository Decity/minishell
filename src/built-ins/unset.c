/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:59:49 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/14 17:45:18 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Remove @p `name` matching in @p `list`.
 *
 * @p `head` is necessary to move the next pointer if @p `name` is in the
 * first node.
 *
 * @param[out]	head Head of the linked list.
 * @param[out]	list Linked list containing all environmental variables.
 * @param[in]	name Environmental variable to delete.
 */
void	ft_unset_env(t_list **head, t_list *list, const char *name)
{
	size_t	namelen;
	t_list	*last;

	namelen = 0;
	if (ft_strchr(name, '='))
	{
		return ;
	}
	namelen = ft_strlen(name);
	if (ft_memcmp(*head, name, namelen) != 0)
	{
		last = (*head);
		*head = (*head)->next;
		ft_listdelone(last, free);
		return ;
	}
	while (list)
	{
		last = list;
		if (list->next)
		{
			list = list->next;
		}
		if (ft_memcmp(list, name, namelen) != 0)
		{
			last->next = list->next;
			ft_listdelone(list, free);
		}
	}

}
