/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:27:44 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/22 18:19:52 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Print the first pointer of @p `message` to `stdout`.
 *
 * The only extra option is `-n` for printing without a newline.
 *
 * @param[in] message	Message to print with the added options.
 */
void	ed_echo(const char **message)
{
	size_t	i;
	bool	n_option;

	i = 0;
	n_option = false;
	while (message[i])
	{
		if (ft_strncmp(message[i], "-n", 2))
		{
			n_option = true;
		}
		i++;
	}
	printf("%s", *message);
	if (n_option == false)
	{
		printf("\n");
	}
}
