/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:16:18 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/26 15:16:24 by dbakker          ###   ########.fr       */
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
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (data->tokens[j + i])
	{
		if (get_token_type(data->tokens[j + i]) != TYPE_PIPE && data->tokens[j + i] != NULL)
		{
			i++;
			continue ;
		}
		new = ed_cmdnew(data->tokens + j, i++ - 1);
		if (new == NULL)
			return (NULL);
		ed_cmdadd_back(&data->command, new);
		j = i;
		i = 0;
	}
	return (data);
}
// ["ls", "-l", "-a", "|", "grep", "filename", NULL]
// [0   , 1   , 2   , 3  , 4     , 5         , 6   ]

// ["ls", "-l", "-a", NULL]
// [0   , 1   , 2   , 3   ]

// ["grep", "filename", NULL]
// [0     , 1         , 2   ]