/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:16:57 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/17 10:07:28 by dbakker          ###   ########.fr       */
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
static bool	is_env_name(const char *str)
{
	size_t	i;

	i = 0;
	if (*str == '\0')
	{
		return (false);
	}
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
 * @brief Check if @p `envvar` matches the `NAME` in `content` of @p
 * @brief `curr_node`.
 *
 * @param[out]	curr_node	`content` to replace.
 * @param[in]	envvar		The new environmental variable.
 *
 * @retval New pointer to `content` of @p `curr_node` if both arguments match.
 * @retval Pointer to `content` of @p `curr_node` if neither arguments match.
 * @retval `NULL` on failure.
 *
 * @warning Caller owns free().
 */
static void	*try_replacing_existing_env(t_list *curr_node, const char *envvar)
{
	size_t	len_envvar;
	size_t	len_cnt;
	char	*str;

	len_envvar = env_namelen(envvar);
	len_cnt = env_namelen(curr_node->content);
	if (ft_memcmp(curr_node->content, envvar, len_cnt) == 0
		&& len_envvar == len_cnt)
	{
		str = ft_strdup(envvar);
		if (str == NULL)
			return (NULL);
		free(curr_node->content);
		curr_node->content = str;
		return (curr_node->content);
	}
	return (curr_node->content);
}

/**
 * @brief Add @p `envvar` to the end of @p `list`.
 *
 * If the `NAME` of @p `envvar` matches that of an already existing environmental
 * variable, it will instead replace the variable.
 * If allocation for the new environmental variable fails, the current one will
 * remain unchanged.
 *
 * @param[out]	list	Linked list containing all environmental variables.
 * @param[in]	envvar	Environmental variable to add to the linked list.
 *
 * @return Pointer to the node added to the list, or `NULL` on failure.
 *
 * @warning Caller owns free().
 *
 * @note @p `envvar` can only contain alphabetical characters, numbers and
 * @note underscores, but cannot start with numbers.
 */
void	*export_env(t_list *list, const char *envvar)
{
	t_list	*curr_node;
	void	*old_ptr;
	void	*new_ptr;

	if (ft_isdigit(*envvar) || is_env_name(envvar) == false)
		return (NULL);
	curr_node = list;
	while (curr_node)
	{
		old_ptr = curr_node->content;
		new_ptr = try_replacing_existing_env(curr_node, envvar);
		if (new_ptr == NULL)
			return (NULL);
		else if (new_ptr != old_ptr)
			return (curr_node);
		curr_node = curr_node->next;
	}
	curr_node = ft_listnew((char *)envvar);
	if (curr_node == NULL)
		return (NULL);
	ft_listadd_back(&list, curr_node);
	return (ft_listlast(list));
}
