/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:16:18 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/23 16:04:51 by dbakker          ###   ########.fr       */
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
	cmd->redirection.output_fd = STDOUT_FILENO;
	cmd->next = NULL;
	return (cmd);
}

void	ed_cmdadd_back(t_cmd **head, t_cmd *new)
{
	t_cmd	*node;

	node = *head;
	if (head == NULL)
	{
		*head = new;
		return ;
	}
	while (node->next)
	{
		node = node->next;
	}
	node->next = new;
}

void	*file_redirection(t_cmd *cmd, size_t index, uint8_t redirection_type)
{
	static size_t	i_input;
	static size_t	i_output;

	i_input = 0;
	i_output = 0;
	if (redirection_type != 0)
		{
			if (cmd->redirection.redirection_type == TYPE_REDIRECTION_IN)
			{
				cmd->redirection.infile[i_input] = ft_strdup(cmd->arguments[index]);
			}
			else if (cmd->redirection.redirection_type == TYPE_REDIRECTION_OUT)
			{
				cmd->redirection.outfile[i_output] = ft_strdup(cmd->arguments[index]);
			}
			else if (cmd->redirection.redirection_type == TYPE_REDIRECTION_APPEND)
			{
				cmd->redirection.outfile[i_output] = ft_strdup(cmd->arguments[index]);
			}
		}
	return (NULL);
}

void	*init_redirection(t_cmd *cmd)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (cmd->arguments[i])
	{
		cmd->redirection.redirection_type = get_redirection_type(cmd->arguments[i]);
		file_redirection(cmd, i, cmd->redirection.redirection_type);
		i++;
	}

	return (NULL);
}

void	*ed_parsing(t_data *data)
{
	t_cmd	*new;
	size_t	i;

	i = 0;
	while (data->tokens[i])
	{
		if (get_token_type(data->tokens[i]) == TYPE_PIPE)
		{
			new = ed_cmdnew(data->tokens, i);
			ed_cmdadd_back(&data->command, new);
		}
		i++;
	}

}
