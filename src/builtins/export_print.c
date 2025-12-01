/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 09:57:35 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/01 14:34:14 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Print out all environmental variables to `stdout`.
 *
 * Should be used if `export` gets called without arguments. At which variables
 * get printed as `declare -x NAME="VALUE"`.
 */
int	export_print(const t_list *list)
{
	const char	declare_x[] = "declare -x ";

	while (list)
	{
		write(STDOUT_FILENO, declare_x, sizeof(declare_x) - 1);
		write(STDOUT_FILENO, list->content, env_namelen((char *)list->content));
		printf("=\"%s\"\n", ft_getenv(list, (char *)list->content));
		list = list->next;
	}
	return (0);
}
