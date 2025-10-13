/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 22:47:22 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/13 23:13:31 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Convert the array of environment variables into a linked list.
 *
 * Each ->next is equivalent of iterating through an array.
 *
 * @param[in] envp Array of environment variables.
 *
 * @return Pointer to the linked list, or `NULL` on failure.
 *
 * @warning Caller owns free().
 */
t_list	*envp_to_llist(const char **envp)
{
	t_list	*list;
	char	*str;
	size_t	i;

	list = NULL;
	i = 0;
	while (envp[i])
	{
		str = ft_strdup(envp[i]);
		// TODO: Malloc error handling
		ft_listadd_back(&list, ft_listnew(str));
		i++;
	}
	return (list);
}

/**
 * @brief Print all environment variables to `stdout`.
 */
void	env_print(const t_list *envp)
{
	while (envp)
	{
		printf("%s\n", (char *)envp->content);
		envp = envp->next;
	}
}