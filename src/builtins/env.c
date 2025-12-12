/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 22:47:22 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/12 12:52:15 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @return The length of @p `str` until it encounters the `=` delimiter.
 */
size_t	env_namelen(const char *str)
{
	size_t	namelen;

	namelen = 0;
	while (str[namelen] && str[namelen] != '=')
	{
		namelen++;
	}
	return (namelen);
}

/**
 * @return The length of @p `str` after the `=` delimiter.
 *
 * @note Behaviour is undefined if no delimiter is found.
 */
size_t	env_valuelen(const char *str)
{
	size_t	namelen;
	size_t	valuelen;

	if (ft_strchr(str, '=') == NULL)
	{
		return (0);
	}
	namelen = env_namelen(str) + 1;
	valuelen = 0;
	while (str[namelen])
	{
		namelen++;
		valuelen++;
	}
	return (valuelen);
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
	const size_t	namelen = ft_strlen(name);
	size_t			envlen;

	list = list->next;
	while (list)
	{
		envlen = env_namelen(list->content);
		if (namelen > envlen)
		{
			if (ft_memcmp(list->content, name, namelen) == 0)
			{
				return (ft_strchr(list->content, '=') + 1);
			}
		}
		else
		{
			if (ft_memcmp(list->content, name, envlen) == 0)
			{
				return (ft_strchr(list->content, '=') + 1);
			}
		}
		list = list->next;
	}
	return (NULL);
}

/**
 * @brief Compare the first @p `num` bytes of @p `name` in @p `list` and
 * @brief return its `VALUE`.
 *
 * Use this function if @p `name` contains more than just the variable.
 *
 * @param[in] list	Linked list containing environmental variables.
 * @param[in] name	`NAME` to find in linked list.
 * @param[in] num	The amount of bytes to compare.
 *
 * @return Pointer to the `VALUE` of `NAME`, or `NULL` if not found.
 */
char	*ft_getnenv(const t_list *list, const char *name, size_t num)
{
	list = list->next;
	while (list)
	{
		if (env_namelen(list->content) != num)
		{
			list = list->next;
			continue ;
		}
		if (ft_memcmp(list->content, name, num) == 0)
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
int	builtin_env_print(const t_list *envp)
{
	while (envp)
	{
		if (ft_strchr(envp->content, '='))
		{
			printf("%s\n", (char *)envp->content);
		}
		envp = envp->next;
	}
	return (0);
}
