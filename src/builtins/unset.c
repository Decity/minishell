/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:59:49 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/11 14:41:54 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Validate that a string is a valid environment variable name.
 *
 * Valid names must start with a letter or underscore, and contain only
 * alphanumeric characters and underscores.
 *
 * @param[in]	str	String to validate.
 *
 * @retval true if the string is a valid variable name.
 * @retval false if the string is invalid (NULL, empty, starts with digit,
 *               or contains invalid characters).
 */
static bool	is_valid_unset_name(const char *str)
{
	size_t	i;

	if (!str || *str == '\0' || ft_isdigit(*str))
		return (false);
	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

/**
 * @return `true` if `content` of @p `head` matches @p `name`, false otherwise.
 */
static bool	unset_head(t_list **head, const char *name)
{
	const size_t	namelen = ft_strlen(name);
	const size_t	envlen = env_namelen((*head)->content);
	t_list			*last;

	if (namelen > envlen)
	{
		if (ft_memcmp((*head)->content, name, namelen) == 0)
		{
			last = (*head);
			*head = (*head)->next;
			ft_listdelone(last, free);
			return (true);
		}
	}
	else
	{
		if (ft_memcmp((*head)->content, name, envlen) == 0)
		{
			last = (*head);
			*head = (*head)->next;
			ft_listdelone(last, free);
			return (true);
		}
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
static int	unset_variable(t_list **head, const char *name)
{
	const size_t	namelen = ft_strlen(name);
	size_t			envlen;
	t_list			*node;
	t_list			*last;

	if (name == NULL || !is_valid_unset_name(name)
		|| unset_head(head, name) == true)
		return (0);
	node = *head;
	while (node)
	{
		last = node;
		node = node->next;
		if (node)
		{
			envlen = env_namelen(node->content);
			if (namelen > envlen)
				envlen = namelen;
			if (ft_memcmp(node->content, name, envlen) == 0)
			{
				return (last->next = node->next, ft_listdelone(node, free), 0);
			}
		}
	}
	return (0);
}

/**
 * @brief Unset one or more environment variables.
 *
 * Removes the specified environment variables from the environment list.
 * Invalid variable names are silently ignored. Matches bash behavior where
 * unset always returns 0.
 *
 * @param[in,out]	head	Pointer to the head of the environment list.
 * @param[in]		args	Command arguments (args[0] is "unset", args[1+] are
 *                          variable names to unset).
 *
 * @return Always returns 0 (success).
 */
int	builtin_unset(t_list **head, char **args)
{
	int	i;

	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		unset_variable(head, args[i]);
		i++;
	}
	return (0);
}
