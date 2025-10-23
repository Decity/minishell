/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:27:44 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/22 18:46:51 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Print all pointers of @p `message` to `stdout`,
 *
 * If the first pointer of @p `message` contains `-n`, no newline will be
 * printed.
 *
 * @param[in] message Messages to print.
 */
void	ed_echo(const char **message)
{
	size_t	i;
	bool	n_option;

	i = 0;
	n_option = false;
	while (message[i])
	{
		if (ft_strncmp(message[i], "-n", 2) == 0)
		{
			n_option = true;
		}
		else
		{
			break ;
		}
		i++;
	}
	while (message[i])
	{
		printf("%s", message[i]);
		i++;
	}
	if (n_option == false)
		printf("\n");
}
