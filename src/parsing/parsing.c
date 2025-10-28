/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:16:18 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/26 17:20:51 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Turn the tokenized arguments into a linked list, split along each `|`.
 *
 * @param[in] data Pointer containing tokenized arguments.
 *
 * @return Pointer to the updated list, or NULL on failure.
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
			new = init_cmd(data, index - start);
			if (new == NULL)
				return (NULL);
			ed_cmdadd_back(&data->command, new);
			start = index + 1;
		}
		index++;
	}
	if (start < index)
	{
		new = ed_cmdnew((const char **)(data->tokens + start), index - start);
		if (new == NULL)
			return (NULL);
		ed_cmdadd_back(&data->command, new);
	}
	return (data);
}
// ["ls", "-l", "-a", "|", "grep", "filename", NULL]
// [0   , 1   , 2   , 3  , 4     , 5         , 6   ]

// ["ls", "-l", "-a", NULL]
// [0   , 1   , 2   , 3   ]

// ["grep", "filename", NULL]
// [0     , 1         , 2   ]