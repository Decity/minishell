/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:16:18 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/08 11:09:19 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Add a new command struct to the end of the linked list
 *
 * @param[out]	data	Data struct containing a linked list of command structs.
 * @param[in]	tokens	Array of commandline arguments.
 * @param[in]	size	Amount of tokens to copy.
 *
 * @warning Caller owns `free()`.
 */
static void	*parsing_add_cmd(t_data *data, const char **tokens, size_t size)
{
	t_cmd	*new;

	new = parsing_init(tokens, size);
	if (new == NULL)
	{
		return (NULL);
	}
	cmdadd_back(&data->command, new);
	return (new);
}

/**
 * @brief Turn the tokenized arguments into a linked list, split along each `|`.
 *
 * @param[in,out] data Pointer containing tokenized arguments.
 *
 * @return Pointer to the updated list, or `NULL` on failure.
 *
 * @warning Caller owns `free()`.
 */
t_data	*parsing(t_data *data)
{
	size_t	start;
	size_t	index;

	start = 0;
	index = 0;
	while (data->tokens[index])
	{
		if (get_token_type(data->tokens[index]) == TYPE_PIPE)
		{
			if (parsing_add_cmd(data, (const char **)data->tokens + start,
					index - start) == NULL)
				return (perror("minishell"), NULL);
			start = index + 1;
		}
		index++;
	}
	if (start < index)
		if (parsing_add_cmd(data, (const char **)data->tokens + start,
				index - start) == NULL)
			return (perror("minishell"), NULL);
	return (data);
}
