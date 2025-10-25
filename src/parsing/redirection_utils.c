/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:14:19 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/25 19:14:46 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redir_in(char *argument)
{
	if (*argument == '<' || ft_strncmp(argument, "<<", 2) == 0)
	{
		return (true);
	}
	return (false);
}

bool	is_redir_out(char *argument)
{
	if (*argument == '>' || ft_strncmp(argument, ">>", 2) == 0)
	{
		return (true);
	}
	return (false);
}

size_t	count_redir_in(char **arguments)
{
	size_t	i;
	size_t	input_count;

	i = 0;
	input_count = 0;
	while (arguments[i])
	{
		if (is_redir_in(arguments[i]))
		{
			input_count++;
		}
		i++;
	}
	return (input_count);
}

size_t	count_redir_in(char **arguments)
{
	size_t	i;
	size_t	output_count;

	i = 0;
	output_count = 0;
	while (arguments[i])
	{
		if (is_redir_out(arguments[i]))
		{
			output_count++;
		}
		i++;
	}
	return (output_count);
}