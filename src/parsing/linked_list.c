/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:05:42 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/09 17:54:25 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isredirection(char *token)
{
	const char		*rdr[] = {">", "<", ">>", "<<", "|", NULL};
	const size_t	tokenlen = ft_strlen(token);
	size_t			i;

	i = 0;
	while (rdr[i])
	{
		ft_printf("Comparing %s with %s\n", token, rdr[i]);
		if (ft_strncmp(token, rdr[i], tokenlen) == 0)
		{
			return (true);
		}
		i++;
	}
	return (false);
}

t_commands	*doubly_linked_list(char **tokens)
{
	t_commands	cmd;
	size_t		i;

	i = 0;
	while (tokens[i])
	{
		ft_isredirection(tokens[i]);
		i++;
	}
	return (NULL);
}

// /**
//  * @return Pointer to the last node in @p `list`.
//  */
// t_list	*ft_listlast(t_list *list)
// {
// 	if (list == NULL)
// 	{
// 		return (NULL);
// 	}
// 	while (list->next != NULL)
// 	{
// 		list = list->next;
// 	}
// 	return (list);
// }

// /**
//  * @brief Store @p `content` to the member variable `content` of `t_list`.
//  *
//  * @param[in] content Content to add.
//  *
//  * @return Pointer to the new node, or `NULL` on failure.
//  *
//  * @warning Caller owns free().
//  */
// t_list	*ft_listnew(void *content)
// {
// 	t_list	*node;

// 	node = malloc(sizeof(t_list));
// 	if (node == NULL)
// 	{
// 		return (NULL);
// 	}
// 	node->content = content;
// 	node->next = NULL;
// 	return (node);
// }

// void	ft_listadd_front(t_list **list, t_list *new)
// {
// 	if (list == NULL || new == NULL)
// 	{
// 		return ;
// 	}
// 	new->next = *list;
// 	*list = new;
// }

// /**
//  * @brief Append @p `new` to @p `list`.
//  *
//  * @param[out]	list	List to append to.
//  * @param[in]	new		Node to be appended.
//  */
// void	ft_listadd_back(t_list **list, t_list *new)
// {
// 	t_list	*node;

// 	node = *list;
// 	if (*list == NULL)
// 	{
// 		*list = new;
// 		return ;
// 	}
// 	while (node->next)
// 	{
// 		node = node->next;
// 	}
// 	node->next = new;
// }

// void	ft_listdelone(t_list *list, void (*del)(void *))
// {
// 	if (list == NULL || del == NULL)
// 	{
// 		return ;
// 	}
// 	del(list->content);
// 	free(list);
// }

// /**
//  * @brief Free the given node and all its successors.
//  *
//  * @param[in,out]	list	Pointer to the head pointer.
//  * @param[in]		del		Function to delete each node in @p `list`.
//  */
// void	ft_listclear(t_list **list, void (*del)(void *))
// {
// 	t_list	*node;
// 	t_list	*temp;

// 	if (list == NULL || *list == NULL)
// 	{
// 		return ;
// 	}
// 	node = *list;
// 	while (node)
// 	{
// 		temp = node->next;
// 		ft_listdelone(node, del);
// 		node = temp;
// 	}
// 	*list = NULL;
// }
