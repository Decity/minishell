/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:27:44 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/09 17:19:10 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @return `true` if @p `message` contains the `-n` option, `false` otherwise.
 */
static bool	builtin_echo_option_n(const char *message)
{
	size_t	i;

	i = 0;
	if (message[i] != '-')
	{
		return (false);
	}
	i += 1;
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
 * @brief Print all pointers of @p `messages` to `stdout`,
 *
 * If the first pointer of @p `messages` contains `-n`, no newline will be
 * printed.
 *
 * @param[in] messages Messages to print.
 */
int	builtin_echo(const char **messages)
{
	ssize_t	i;
	bool	n_option;

	i = -1;
	n_option = false;
	while (messages[++i])
	{
		if (builtin_echo_option_n(messages[i]) == true)
		{
			n_option = true;
			continue ;
		}
		break ;
	}
	while (messages[i])
	{
		if (messages[i + 1] == NULL || *messages[i] == '\0')
			printf("%s", messages[i]);
		else
			printf("%s ", messages[i]);
		i += 1;
	}
	if (n_option == false && *messages)
		printf("\n");
	return (0);
}
