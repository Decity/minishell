/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:16:57 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/15 17:52:13 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if @p `str` only contains allowed characters for environmental
 * @brief `NAME`.
 *
 * Allowed characters are lowercase/uppercase alphabetical characters,
 * digits and underscores.
 *
 * @param[in] str String to check.
 *
 * @return `false` if an invalid character is found, `true` otherwise.
 */
bool	is_env_name(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
		{
			return (false);
		}
		i++;
	}
	return (true);
}

/**
 * @brief Add @p `envvar` to the end of @p `list`.
 *
 * If the `NAME` of @p `envvar` matches that of an already existing environmental
 * variable, it will instead replace the variable.
 *
 * @param[out]	list	Linked list containing all environmental variables.
 * @param[in]	envvar	Environmental variable to add to the linked list.
 *
 * @return Pointer to the node added to the list, or `NULL` on failure.
 *
 * @warning Callers owns free().
 *
 * @note @p `envvar` can only contain alphabetical characters, numbers and
 * @note underscores, but cannot start with numbers.
 */
void	*export_env(t_list *list, const char *envvar)
{
	t_list	*node;
	size_t	envvarlen;
	size_t	contentlen;

	if (ft_isdigit(*envvar) || is_env_name(envvar) == false)
	{
		return (NULL);
	}
	node = list;
	envvarlen = env_namelen(envvar);
	while (node)
	{
		contentlen = env_namelen(node->content);
		if (ft_memcmp(node->content, envvar, contentlen) == 0 && envvarlen == contentlen)
		{
			free(node->content);
			node->content = ft_strdup(envvar);
			return (node);
		}
		node = node->next;
	}
	ft_listadd_back(&list, ft_listnew((char *)envvar));
	return (ft_listlast(list));
}
