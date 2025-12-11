/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:59:49 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/11 17:36:49 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_unset_var(t_list **head, const char *name)
{
	const size_t	namelen = ft_strlen(name);
	size_t			envlen;
	t_list			*last;
	t_list			*node;

	node = *head;
	while (node)
	{
		last = node;
		node = node->next;
		if (node)
		{
			envlen = env_namelen((const char *)node->content);
			if (namelen > envlen)
				envlen = namelen;
			if (ft_memcmp(node->content, name, envlen) == 0)
			{
				last->next = node->next;
				ft_listdelone(node, free);
				return ;
			}
		}
	}
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
int	builtin_unset(t_list **head, char **args)
{
	size_t	i;

	i = 1;
	if (args == NULL)
		return (EXIT_SUCCESS);
	while (args[i])
	{
		builtin_unset_var(head, args[i]);
		i += 1;
	}
	return (EXIT_SUCCESS);
}
