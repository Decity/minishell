/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:53:02 by dbakker           #+#    #+#             */
/*   Updated: 2025/11/27 22:11:39 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			i += 1;
		}
		i = 0;
		node = node->next;
	}
	return (cmd);
}

/**
 * @return `false` if there are more than 16 heredoc redirections or if
 * @return initialization failed, `true` otherwise.
 *
 * @warning `Caller owns free()`.
 */
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

/**
 * @brief Imitate the bash heredoc behaviour.
 *
 * @param[in] cmd	Command struct containing the file descriptor to write to.
 * @param[in] envp	Linked list containing all environmental variables.
 * @param[in] i		Index of the command struct to access.
 */
t_cmd	*heredoc_readline(const t_cmd *cmd, const t_list *envp, const size_t i)
{
	static size_t	line_count = 0;
	char			*line;
	char			*expand;

	while (true != false)
	{
		line = readline(NULL);
		line_count += 1;
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
		line = heredoc_expansion(envp, line);
		if (line == NULL)
			return (NULL);
		ft_putendl_fd(line, cmd->redirect.infile[i].fd);
		free(line);
	}
	return ((t_cmd *)cmd);
}

/**
 * @brief Create and write to a temporary file for each heredoc redirection.
 *
 * @param[in,out]	cmd		Command struct that contains a heredoc redirection.
 * @param[in]		envp	Linked list containing environmental variables.
 *
 * @return Pointer to @p `cmd`, or NULL on failure.
 */
void	*heredoc_create_file(t_cmd *cmd, const t_list *envp)
{
	size_t	i;

	i = 0;
	while (cmd->redirect.infile[i].file)
	{
		if (cmd->redirect.infile[i].redir_type == TYPE_REDIRECTION_HEREDOC)
		{
			cmd->redirect.infile[i].fd = open(cmd->redirect.infile[i].file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (cmd->redirect.infile[i].fd == -1)
				return (NULL);
			heredoc_readline(cmd, envp, i);
			close(cmd->redirect.infile[i].fd);
		}
		i += 1;
	}
	return (cmd);
}

t_data	*heredoc(t_data *data)
{
	t_cmd	*cmd;

	if (DEBUG)
		printf("=== Heredoc begin ===\n");

	if (heredoc_check(data) == false)
		return (NULL);
	cmd = data->command;
	while (cmd)
	{
		heredoc_create_file(cmd, data->envp);
		cmd = cmd->next;
	}
	if (DEBUG)
		printf("=== Heredoc end ===\n");
	return (data);
}
