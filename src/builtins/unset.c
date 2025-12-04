/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:59:49 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/01 14:41:35 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @return `true` if `content` of @p `head` matches @p `name`, false otherwise.
 */
static bool	unset_head(t_list **head, const char *name)
{
	t_list	*last;

	if (ft_memcmp((*head)->content, name, env_namelen((*head)->content)) == 0)
	{
		last = (*head);
		*head = (*head)->next;
		ft_listdelone(last, free);
		return (true);
	}
	return (false);
}

/**
 * @brief Remove @p `name` matching in @p `list`.
 *
 * @p `head` is necessary to move to the next pointer if @p `name` is in the
 * first node.
 *
 * @param[out]	head Head of the linked list.
 * @param[in]	name Environmental variable to delete.
 */
int	builtin_unset(t_list **head, const char *name)
{
	t_list	*node;
	t_list	*last;

	if (name == NULL || ft_strchr(name, '=') || unset_head(head, name) == true)
	{
		return (0);
	}
	node = *head;
	while (node)
	{
		last = node;
		node = node->next;
		if (node)
		{
			if (ft_memcmp(node->content, name, env_namelen(node->content)) == 0)
			{
				last->next = node->next;
				ft_listdelone(node, free);
				return (0);
			}
		}
	}
	return (0);
}
