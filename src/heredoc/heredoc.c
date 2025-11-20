/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:53:02 by dbakker           #+#    #+#             */
/*   Updated: 2025/11/20 15:56:05 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Closes and unlinks all generated files for the heredocs.
 */
void	remove_heredoc_files(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (cmd)
	{
		while (cmd->redirect.infile[i].file)
		{
			if (cmd->redirect.infile[i].redir_type == TYPE_REDIRECTION_HEREDOC)
			{
				close(cmd->redirect.infile[i].fd);
				unlink(cmd->redirect.infile[i].file);
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

bool	heredoc_check(t_data *data)
{
	if (count_redir_heredoc((const char **)data->tokens) > HEREDOC_LIMIT)
	{
		return (false);
	}
	if (init_heredoc(data->command) == NULL)
	{
		return (false);
	}
	return (true);
}

void	heredoc_readline(t_cmd *cmd, size_t i)
{
	static size_t	line_count = 0;
	char			*line;

	while (true != false)
	{
		line = readline(NULL);
		line_count++;
		if (line == NULL)
		{
			heredoc_print_warning(line_count, cmd->redirect.infile[i].delimiter);
			break ;
		}
		if (strcmp(line, cmd->redirect.infile[i].delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, cmd->redirect.infile[i].fd);
		free(line);
	}
}

void	*heredoc_file_insertion(t_cmd *cmd)
{
	size_t			i;

	i = 0;
	while (cmd->redirect.infile[i].file)
	{
		if (cmd->redirect.infile[i].redir_type == TYPE_REDIRECTION_HEREDOC)
		{
			cmd->redirect.infile[i].fd = open(cmd->redirect.infile[i].file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (cmd->redirect.infile[i].fd)
				return (NULL);
			heredoc_readline(cmd, i);
			close(cmd->redirect.infile[i].fd);
		}
		i++;
	}
	return (cmd);
}

t_data	*heredoc(t_data *data)
{
	if (DEBUG)
		printf("=== Heredoc begin ===\n");

	if (heredoc_check(data) == false)
		return (NULL);

	heredoc_file_insertion(data->command);
	if (DEBUG)
		printf("=== Heredoc end ===\n");
	return (data);
}
