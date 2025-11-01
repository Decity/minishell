/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:16:18 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/30 11:12:39 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Turn the tokenized arguments into a linked list, split along each `|`.
 *
 * @param[in,out] data Pointer containing tokenized arguments.
 *
 * @return Pointer to the updated list, or `NULL` on failure.
 *
 * @warning Caller owns free().
 */
t_data	*ed_parsing(t_data *data)
{
	t_cmd	*new;
	size_t	start;
	size_t	index;

	start = 0;
	index = 0;
	while (data->tokens[index])
	{
		if (get_token_type(data->tokens[index]) == TYPE_PIPE)
		{
			new = init_cmd((const char **)data->tokens + start, index - start);
			if (new == NULL)
				return (NULL);
			ed_cmdadd_back(&data->command, new);
			start = index + 1;
		}
		index++;
	}
	if (start < index)
	{
		new = init_cmd((const char **)data->tokens + start, index - start);
		if (new == NULL)
			return (NULL);
		ed_cmdadd_back(&data->command, new);
	}
	return (data);
}
