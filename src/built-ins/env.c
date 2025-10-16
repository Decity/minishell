/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 22:47:22 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/15 17:53:16 by dbakker          ###   ########.fr       */
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
	size_t	i;
	char	*str;

	if (array == NULL)
	{
		return (NULL);
	}
	list = NULL;
	i = 0;
	while (array[i])
	{
		str = ft_strdup(array[i]);
		// TODO: Malloc error handling
		ft_listadd_back(&list, ft_listnew(str));
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
	{
		return (NULL);
	}
	i = 0;
	listsize = ft_listsize((t_list *)list);
	array = ft_calloc(listsize + 1, sizeof(char *));
	if (array == NULL)
	{
		return (NULL);
	}
	while (list)
	{
		array[i] = ft_strdup(list->content);
		if (array[i] == NULL)
		{
			// TODO: Malloc error handling.
			return (NULL);
		}
		list = list->next;
		i++;
	}
	return (array);
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
