/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:53:02 by dbakker           #+#    #+#             */
/*   Updated: 2025/11/15 15:09:42 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Closes and unlinks all generated files for the heredocs.
 */
void	remove_heredoc_files(t_cmd *cmd)
{
	size_t	i;
	int		ret_unlink;
	int		ret_close;

	i = 0;
	while (cmd)
	{
		while (cmd->redirect.heredoc[i].filename)
		{
			ret_close = close(cmd->redirect.heredoc[i].fd);
			ret_unlink = unlink(cmd->redirect.heredoc[i].filename);
			i++;
		}
		i = 0;
		cmd = cmd->next;
	}
}

/**
 * @brief Initializes all command structs with a file for the heredoc to write
 * @brief to.
 *
 * @param[out] cmd Command struct to initialize.
 *
 * @return Pointer to @p `cmd`, or `NULL` on failure.
 *
 * @warning Caller owns free().
 */
void	*init_heredoc(t_cmd *cmd)
{
	t_cmd	*node;
	size_t	i;

	i = 0;
	node = cmd;
	while (node)
	{
		while (node->redirect.heredoc[i].delimiter)
		{
			node->redirect.heredoc[i].filename = generate_heredoc_name();
			if (node->redirect.heredoc[i].filename == NULL)
			{
				return (NULL);
			}
			i++;
		}
		i = 0;
		node = node->next;
	}
	return (cmd);
}

t_data	*heredoc(t_data *data)
{
	char	*line;
	size_t	i;

	if (count_redir_heredoc((const char **)data->tokens) > HEREDOC_LIMIT)
	{
		return (NULL);
	}
	if (init_heredoc(data->command) == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (data->command->redirect.heredoc[i].delimiter)
	{
		data->command->redirect.heredoc[i].fd = open(data->command->redirect.heredoc[i].filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		while (true)
		{
			line = readline(NULL);
			if (ft_strcmp(line, data->command->redirect.heredoc[i].delimiter) == 0)
			{
				break ;
			}
			ft_putendl_fd(line, data->command->redirect.heredoc[i].fd);
		}
		i++;
	}
	return (data);
}
