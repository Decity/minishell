/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:16:57 by dbakker           #+#    #+#             */
/*   Updated: 2025/11/23 12:01:49 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if @p `str` only contains allowed characters for environmental
 * @brief `NAME`.
 *
 * Allowed characters are lowercase/uppercase alphabetical characters,
 * digits and underscores, but may not have digits as the first character.
 *
 * @param[in] str String to check.
 *
 * @return `false` if an invalid character is found, `true` otherwise.
 */
bool	is_env_name(const char *str)
{
	size_t	i;

	i = 0;
	if (*str == '\0' || ft_isdigit(*str))
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

bool	has_env_value(const char *envvar)
{
	if (ft_strchr(envvar, '=') == NULL)
	{
		return (false);
	}
	return (true);
}

/**
 * @brief Add @p `envvar` to the end of @p `list`.
 *
 * If the `NAME` of @p `envvar` matches that of an already existing environmental
 * variable, and contains `=`, it will instead replace the variable.
 * If allocation for the new environmental variable fails, the current one will
 * remain unchanged.
 *
 * @param[out]	list	Linked list containing all environmental variables.
 * @param[in]	envvar	Environmental variable to add to the linked list.
 *
 * @retval Pointer to the node added to the list.
 * @retval Pointer to @p `list`.
 * @retval `NULL` on failure.
 *
 * @warning Caller owns free().
 *
 * @note @p `envvar` can only contain alphabetical characters, numbers and
 * @note underscores, but cannot start with numbers.
 */
void	*export_env(t_list *list, const char *envvar)
{
	t_list	*curr_node;
	char	*str_env;
	void	*ptr_old;
	void	*ptr_new;

	if (is_env_name(envvar) == false)
		return (NULL);
	if (has_env_value(envvar) == false)
		return (list);
	str_env = ft_strdup(envvar);
	if (str_env == NULL)
		return (NULL);
	curr_node = list;
	while (curr_node)
	{
		ptr_old = curr_node->content;
		ptr_new = try_replacing_existing_env(curr_node, str_env);
		if (ptr_new == NULL)
			return (NULL);
		else if (ptr_new != ptr_old)
			return (curr_node);
		curr_node = curr_node->next;
	}
	curr_node = ft_listnew((char *)str_env);
	if (curr_node == NULL)
		return (NULL);
	ft_listadd_back(&list, curr_node);
	return (ft_listlast(list));
}

/**
 * @brief Print out all environmental variables to `stdout`.
 *
 * Should be used if `export` gets called without arguments. At which variables
 * get printed as `declare -x NAME="VALUE"`.
 */
void	export_print(const t_list *list)
{
	const char declare_x[] = "declare -x ";

	while (list)
	{
		write(STDOUT_FILENO, declare_x, sizeof(declare_x) - 1);
		write(STDOUT_FILENO, list->content, env_namelen((char *)list->content));
		printf("=\"%s\"\n", ft_getenv(list, (char *)list->content));
		list = list->next;
	}
}
