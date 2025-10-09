/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:52:25 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/09 12:47:26 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Store @p `content` to the member variable `content` of `t_list`.
 *
 * @param[in] content Content to add.
 *
 * @return Pointer to the new node, or `NULL` on failure.
 *
 * @warning Caller owns free().
 */
t_list	*ft_listnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (node == NULL)
	{
		return (NULL);
	}
	node->content = content;
	node->next = NULL;
	return (node);
}
