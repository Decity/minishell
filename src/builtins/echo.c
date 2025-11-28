/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:27:44 by dbakker           #+#    #+#             */
/*   Updated: 2025/11/28 15:56:14 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	builtin_echo_option(const char *message)
{
	size_t	i;

	i = 0;
	if (message[i] == '-')
	{
		i += 1;
	}
	while (message[i])
	{
		if (message[i] != 'n')
		{
			return (false);
		}
		i += 1;
	}
	return (true);
}

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
		if (builtin_echo_option(message[i]) == true)
		{
			n_option = true;
			i += 1;
		}
		else
			break ;
	}
	while (message[i])
	{
		if (message[i + 1] == NULL)
			printf("%s", message[i]);
		else
			printf("%s ", message[i]);
		i += 1;
	}
	if (n_option == false)
		printf("\n");
}
