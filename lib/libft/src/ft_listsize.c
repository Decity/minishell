/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:00:03 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/09 13:59:36 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @return Size of the linked list.
 */
size_t	ft_listsize(t_list *list)
{
	size_t	list_count;

	list_count = 0;
	while (list)
	{
		list_count++;
		list = list->next;
	}
	return (list_count);
}
