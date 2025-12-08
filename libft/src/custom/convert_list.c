/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:30:14 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/05 14:04:08 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Convert the array of strings into a linked list.
 *
 * Each ->next is equivalent of iterating through an array.
 *
 * @param[in] array Array of strings.
 *
 * @return Pointer to the linked list, or `NULL` on failure.
 *
 * @warning Caller owns free().
 */
t_list	*array_to_llist(const char **array)
{
	t_list	*list;
	t_list	*node;
	size_t	i;
	char	*str;

	if (array == NULL)
		return (NULL);
	list = NULL;
	i = 0;
	while (array[i])
	{
		str = ft_strdup(array[i]);
		if (str == NULL)
		{
			return (ft_listclear(&list, free), NULL);
		}
		node = ft_listnew(str);
		if (node == NULL)
		{
			return (ft_listclear(&list, free), NULL);
		}
		ft_listadd_back(&list, node);
		i++;
	}
	return (list);
}

/**
 * @brief Convert the linked list into an array of strings.
 *
 * Each new index of the array is the equivalent stepping to the next node
 * of the linked list.
 *
 * @param[in] list Linked list.
 *
 * @return Pointer to the Array of strings, or `NULL` on failure.
 *
 * @warning Caller owns free().
 */
char	**llist_to_array(const t_list *list)
{
	char	**array;
	size_t	listsize;
	size_t	i;

	if (list == NULL)
		return (NULL);
	i = 0;
	listsize = ft_listsize((t_list *)list);
	array = ft_calloc(listsize + 1, sizeof(char *));
	if (array == NULL)
		return (NULL);
	while (list)
	{
		array[i] = ft_strdup(list->content);
		if (array[i] == NULL)
		{
			free_array(&array);
			return (NULL);
		}
		list = list->next;
		i++;
	}
	return (array);
}
