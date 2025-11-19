/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:53:02 by dbakker           #+#    #+#             */
/*   Updated: 2025/11/19 15:15:20 by dbakker          ###   ########.fr       */
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
		while (cmd->redirect.infile[i].file)
		{
			if (cmd->redirect.infile[i].redir_type == TYPE_REDIRECTION_HEREDOC)
			{
				ret_close = close(cmd->redirect.infile[i].fd);
				ret_unlink = unlink(cmd->redirect.infile[i].file);
			}
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
		while (node->redirect.infile[i].file || node->redirect.infile[i].delimiter)
		{
			if (node->redirect.infile[i].redir_type == TYPE_REDIRECTION_HEREDOC)
			{
				node->redirect.infile[i].file = generate_heredoc_name();
				if (node->redirect.infile[i].file == NULL)
				{
					return (NULL);
				}
			}
			i++;
		}
		i = 0;
		node = node->next;
	}
	return (cmd);
}
/**
 * The warning it prints out if you CTRL + D in the heredoc.
 */
void	heredoc_print_warning(size_t line_count, const char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document at line ", STDERR_FILENO);
	ft_putnum_fd(line_count, STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

t_data	*heredoc(t_data *data)
{
	static size_t	line_count = 0;
	size_t			i;
	char			*line;

	if (DEBUG)
		printf("=== Heredoc begin ===\n");
	if (count_redir_heredoc((const char **)data->tokens) > HEREDOC_LIMIT)
	{
		return (NULL);
	}
	if (init_heredoc(data->command) == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (data->command->redirect.infile[i].file)
	{
		if (data->command->redirect.infile[i].redir_type == TYPE_REDIRECTION_HEREDOC)
		{
			data->command->redirect.infile[i].fd = open(data->command->redirect.infile[i].file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			while (true)
			{
				line = readline("> ");
				line_count++;
				if (line == NULL)
				{
					heredoc_print_warning(line_count, data->command->redirect.infile[i].delimiter);
					break ;
				}
				if (ft_strcmp(line, data->command->redirect.infile[i].delimiter) == 0)
				{
					break ;
				}
				ft_putendl_fd(line, data->command->redirect.infile[i].fd);
			}
			close(data->command->redirect.infile[i].fd);
			data->command->redirect.infile[i].fd = open(data->command->redirect.infile[i].file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		i++;
	}
	if (DEBUG)
		printf("=== Heredoc end ===\n");
	return (data);
}
