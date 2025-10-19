/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:27:44 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/18 22:49:52 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Print @p `message` to `stdout`.
 *
 * @param[in] message	Message to print
 * @param[in] option	Extra behaviour how @p `message` should be printed.
 */
void	ed_echo(const char *message, const char *option)
{
	if (option == NULL)
	{
		printf("%s\n", message);
	}
	if (ft_memcmp(option, "-n", ft_strlen(option)) == 0)
	{
		printf("%s", message);
	}
}