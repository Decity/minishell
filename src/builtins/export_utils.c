/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:37:23 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/12 13:14:04 by dbakker          ###   ########.fr       */
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
static bool	is_env_name(const char *str)
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
 * @brief Check if @p `str_env` matches the `NAME` in `content` of @p
 * @brief `curr_node` and replace its `VALUE`.
 *
 * @param[out]	curr_node	`content` to replace.
 * @param[in]	str_env		The new environmental variable.
 *
 * @retval New pointer to `content` of @p `curr_node` if both arguments match.
 * @retval Pointer to `content` of @p `curr_node` if both arguments don't match.
 */
static t_list	*builtin_replace_env(t_list *curr_node, const char *str_env)
{
	size_t	len_envvar;
	size_t	len_cnt;

	len_envvar = env_namelen(str_env);
	len_cnt = env_namelen(curr_node->content);
	if (ft_memcmp(curr_node->content, str_env, len_cnt) == 0
		&& len_envvar == len_cnt)
	{
		free(curr_node->content);
		curr_node->content = (void *)str_env;
	}
	return (curr_node->content);
}

/**
 * @brief Iterate through the linked list and either replace an existing
 * @brief variable, or add @p `str_env` to the end of @p `envp`.
 *
 * @param[out]	envp	Linked list containing environmental variables.
 * @param[in]	str_env	String containing a NAME=VALUE pair.
 *
 * @return Pointer to the node added to the list, or `NULL` on failure.
 *
 * @warning Caller owns `free()`.
 */
static t_list	*builtin_iterate_list(t_list *envp, const char *str_env)
{
	t_list	*curr_node;
	void	*ptr_old;
	void	*ptr_new;

	curr_node = envp;
	while (curr_node)
	{
		ptr_old = curr_node->content;
		ptr_new = builtin_replace_env(curr_node, str_env);
		if (ptr_new != ptr_old)
			return (curr_node);
		curr_node = curr_node->next;
	}
	curr_node = ft_listnew((char *)str_env);
	if (curr_node == NULL)
		return (NULL);
	ft_listadd_back(&envp, curr_node);
	return (ft_listlast(envp));
}

/**
 * @brief Add @p `envvar` to the end of @p `envp`.
 *
 * If the `NAME` of @p `envvar` matches that of an already existing
 * environmental variable, and contains `=`, it will instead replace the
 * variable. If allocation for the new environmental variable fails, the current
 * one will remain unchanged.
 *
 * @param[out]	envp	Linked list containing all environmental variables.
 * @param[in]	envvar	Environmental variable to add to the linked list.
 *
 * @return `0` on success, or `1` on failure.
 *
 * @warning Caller owns `free()`.
 *
 * @note @p `envvar` can only contain alphabetical characters, numbers and
 * @note underscores, but cannot start with numbers.
 */
int	builtin_export_var(t_list *envp, char *envvar)
{
	char	*str_env;

	if (envvar == NULL || is_env_name(envvar) == false)
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(envvar, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (ft_strchr(envvar, '=') == NULL && ft_getenv(envp, envvar))
	{
		return (EXIT_SUCCESS);
	}
	str_env = ft_strdup(envvar);
	if (str_env == NULL)
		return (EXIT_FAILURE);
	envp = builtin_iterate_list(envp, str_env);
	return (EXIT_SUCCESS);
}
