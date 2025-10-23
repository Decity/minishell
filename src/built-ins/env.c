/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 22:47:22 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/17 10:40:57 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @return The length of @p `name` until it encounters the `=` delimiter.
 */
size_t	env_namelen(const char *name)
{
	size_t	namelen;

	namelen = 0;
	while (name[namelen] && name[namelen] != '=')
	{
		namelen++;
	}
	return (namelen);
}

/**
 * @brief Find @p `name` in @p `list` and return its `VALUE`.
 *
 * @param[in] list Linked list containing environmental variables.
 * @param[in] name `NAME` to find in linked list.
 *
 * @return Pointer to the `VALUE` of `NAME`, or `NULL` if not found.
 */
char	*ft_getenv(const t_list *list, const char *name)
{
	while (list)
	{
		if (ft_memcmp(list->content, name, env_namelen(list->content)) == 0)
		{
			return (ft_strchr(list->content, '=') + 1);
		}
		list = list->next;
	}
	return (NULL);
}

/**
 * @brief Print all environment variables with a value to `stdout`.
 */
void	env_print(const t_list *envp)
{
	while (envp)
	{
		if (ft_strchr(envp->content, '='))
		{
			printf("%s\n", (char *)envp->content);
		}
		envp = envp->next;
	}
}

/**
 * @brief Print all environment variables to `stdout`.
 */
void	env_all_print(const t_list *envp)
{
	while (envp)
	{
		printf("%s\n", (char *)envp->content);
		envp = envp->next;
	}
}

/**
 * @brief Print the content variable of @p `envp` to `stdout`.
 */
void	env_single_print(const t_list *envp)
{
	printf("%s\n", (char *)envp->content);
}
