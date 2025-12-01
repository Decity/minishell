/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:27:44 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/01 09:47:30 by dbakker          ###   ########.fr       */
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
void	builtin_echo(const char **messages)
{
	size_t	i;
	bool	n_option;

	i = 0;
	n_option = false;
	while (messages[i])
	{
		if (builtin_echo_option_n(messages[i]) == true)
		{
			n_option = true;
			i += 1;
		}
		else
			break ;
	}
	while (messages[i])
	{
		if (messages[i + 1] == NULL)
			printf("%s", messages[i]);
		else
			printf("%s ", messages[i]);
		i += 1;
	}
	if (n_option == false)
		printf("\n");
}
