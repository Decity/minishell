/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:05:42 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/13 08:28:07 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * - Data->tokens: ["echo", "\"hello\", ${TERM}", ">", "test.txt"]
 *
 * - command->arguments: ["echo", "\"hello\", ${TERM}"]
 * - command->redirection: ">"
 * - command->inpput: stdin
 * - command->output: "test.txt"
 */

/**
 * @brief Store @p `content` to the member variable `content` of t_cmds.
 *
 * @param[in] content Content to store.
 *
 * @return Pointer to the new node, or `NULL` on failure.
 *
 * @warning Caller owns free().
 */
t_cmds	*cmd_new(t_parse *content)
{
	t_cmds	*node;

	node = malloc(sizeof(t_cmds));
	if (node == NULL)
	{
		return (NULL);
	}
	node->content = content;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

/**
 * @brief Append @p `new_node` to @p `head`.
 *
 * @param[out]	head		List to append to.
 * @param[in]	new_node	Node to append.
 */
void	cmd_add_back(t_cmds **head, t_cmds *new_node)
{
	t_cmds	*node;
	t_cmds	*second_last_node;

	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	node = *head;
	while (node->next)
	{
		second_last_node = node;
		node = node->next;
	}
	node->next = new_node;
	node->prev = second_last_node;
}

/**
 * @brief Prepend @p `new_node` to @p `head`.
 *
 * @param[out]	head		List to prepend to.
 * @param[in]	new_node	Node to prepend.
 */
void	cmd_add_front(t_cmds **head, t_cmds *new_node)
{
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	new_node->next = *head;
	(*head)->prev = new_node;
	*head = new_node;
}

/**
 * @brief Have @p `prev_node` point to @p `new_node` as the next node.
 *
 * @param[out]	prev_node	The node that @p `new_node` appends to.
 * @param[in]	new_node	The new next node to @p `prev_node`.
 */
void	cmd_add_next(t_cmds *prev_node, t_cmds *new_node)
{
	if (prev_node == NULL)
	{
		return ;
	}
	new_node->next = prev_node->next;
	new_node->prev = prev_node;
	prev_node->next = new_node;
}

/**
 * @brief Have @p `next_node` point to @p `new_node` as the next node.
 *
 * @p `head` is necessary because if @p `next_node` is the head node,
 * it will need to be replaced with the @p `new_node`.
 *
 * @param[out]	head		Pointer to the head node.
 * @param[out]	next_node	The node that @p `new_node` prepends to.
 * @param[in]	new_node	The new previous node to @p `next_node`.
 */
void	cmd_add_prev(t_cmds **head, t_cmds *next_node, t_cmds *new_node)
{
	if (next_node == NULL)
	{
		return ;
	}
	new_node->prev = next_node->prev;
	new_node->next = next_node;
	if (next_node->prev)
	{
		next_node->prev->next = new_node;
	}
	else
	{
		*head = new_node;
	}
	next_node->prev = new_node;
}

/**
 * @brief Check if @p `token` is a redirection.
 *
 * A redirection is `>`, `<`, `>>`, `<<` or `|`.
 *
 * @param[in] token String containing only a single redirection.
 *
 * @return `true` if @p `token` is a redirection, `false` otherwise.
 */
bool	ft_isredirection(const char *token)
{
	const char		*rdr[] = {">", "<", ">>", "<<", "|", NULL};
	const size_t	tokenlen = ft_strlen(token);
	size_t			i;

	i = 0;
	while (rdr[i])
	{
		if (ft_strncmp(token, rdr[i], tokenlen) == 0)
		{
			return (true);
		}
		i++;
	}
	return (false);
}

t_cmds	*doubly_linked_list(char **tokens)
{
	t_cmds	cmd;
	size_t	i;

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
