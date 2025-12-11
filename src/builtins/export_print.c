/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 09:57:35 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/11 18:53:57 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export_var(const char *env_str)
{
	char	*value;
	size_t	namelen;

	if (ft_strchr(env_str, '='))
	{
		namelen = env_namelen(env_str);
		write(STDOUT_FILENO, env_str, namelen);
		write(STDOUT_FILENO, "=\"", 2);
		value = (char *)env_str + namelen + 1;
		ft_putstr_fd(value, STDOUT_FILENO);
		write(STDOUT_FILENO, "\"\n", 2);
	}
	else
		ft_putendl_fd(env_str, STDOUT_FILENO);
}

/**
 * @brief Print out all environmental variables to stdout in sorted order.
 *
 * Variables with values are printed as: export NAME="VALUE"
 * Variables without values are printed as: export NAME
 *
 * @param[in]	list	Linked list of environment variables.
 *
 * @retval 0 on success.
 * @retval 1 on allocation failure.
 */
int	export_print(const t_list *list)
{
	list = list->next;
	while (list)
	{
		print_export_var((const char *)list->content);
		list = list->next;
	}
	return (EXIT_SUCCESS);
}
