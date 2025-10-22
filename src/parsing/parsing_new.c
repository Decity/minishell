/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:16:18 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/22 22:06:05 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ed_cmdnew(const char **arguments, size_t num)
{
	t_cmd	*cmd;

	if (arguments == NULL || *arguments == NULL)
	{
		return (NULL);
	}
	cmd = malloc(sizeof(cmd));
	if (cmd == NULL)
	{
		return (NULL);
	}
	cmd->arguments = copy_narray(arguments, num);
	if (cmd->arguments == NULL)
	{
		return (NULL);
	}
	ft_memset(&cmd->redirection, 0 , sizeof(t_redirection));
	cmd->next = NULL;
	return (cmd);
}

void	*ed_parsing(t_data *data)
{
	size_t	i;

	i = 0;
	while (data->tokens[i])
	{
		if (get_token_type(data->tokens[i]) == TYPE_PIPE)
		{
			data->command = ed_cmdnew(data->tokens, i);
		}
		i++;
	}

}
