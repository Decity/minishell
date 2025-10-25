/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:16:18 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/25 19:14:43 by dbakker          ###   ########.fr       */
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
	ft_memset(&cmd->redirection, 0 , sizeof(t_rdr));
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

t_rdr	*init_redir_in(char **arguments)
{
	t_rdr	*redir_in;
	size_t	i;
	size_t	j;

	redir_in->infile = ft_calloc(count_redir_in(arguments) + 1, sizeof(t_redir));
	if (redir_in->infile == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (arguments[i])
	{
		if (is_redir_in(arguments[i]))
		{
			redir_in->infile[j].redir_type = get_redirection_type(arguments[i]);
			redir_in->infile[j].file = ft_strdup(arguments[i + 1]); // Prone to segfault if the redirection is the last input token.
			if (redir_in->infile[j].file == NULL)
				return (NULL);
			j++;
		}
		i++;
	}
	return (redir_in);
}

t_rdr	*init_redir_out(char **arguments)
{
	t_rdr	*redir_out;
	size_t	i;
	size_t	j;

	redir_out->infile = ft_calloc(count_redir_out(arguments) + 1, sizeof(t_redir));
	if (redir_out->infile == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (arguments[i])
	{
		if (is_redir_out(arguments[i]))
		{
			redir_out->infile[j].redir_type = get_redirection_type(arguments[i]);
			redir_out->infile[j].file = ft_strdup(arguments[i + 1]); // Prone to segfault if the redirection is the last input token.
			if (redir_out->infile[j].file == NULL)
				return (NULL);
			j++;
		}
		i++;
	}
	return (redir_out);
}

t_cmd	*init_redirection(char **arguments)
{
	t_cmd	*redir;

	redir->redirection.infile = init_redir_in(arguments);
	redir->redirection.outfile = init_redir_out(arguments);
	if (redir->redirection.infile == NULL || redir->redirection.outfile == NULL)
	{
		return (NULL);
	}
	return (redir);
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
