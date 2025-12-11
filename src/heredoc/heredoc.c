/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:53:02 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/11 19:13:57 by dbakker          ###   ########.fr       */
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
 * @warning Caller owns `free()`.
 */
static void	*heredoc_init(t_cmd *cmd)
{
	t_cmd	*node;
	size_t	i;

	i = 0;
	node = cmd;
	while (node)
	{
		while (node->rdr.infile[i].file
			|| node->rdr.infile[i].delimiter)
		{
			if (node->rdr.infile[i].redir_type == TYPE_REDIRECTION_HEREDOC)
			{
				node->rdr.infile[i].file = generate_heredoc_name();
				if (node->rdr.infile[i].file == NULL)
				{
					return (redirclear(node->rdr.infile), NULL);
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
 * @brief Imitate the bash heredoc behaviour.
 *
 * @param[in] cmd	Command struct containing the file descriptor to write to.
 * @param[in] envp	Linked list containing all environmental variables.
 * @param[in] idx	Index of the command struct to access.
 */
static t_cmd	*heredoc_readline(const t_cmd *cmd, const t_list *envp,
	size_t idx)
{
	static size_t	line_count = 1;
	char			*line;

	while (true != false)
	{
		line = readline(PROMPT_HEREDOC);
		if (line == NULL)
		{
			heredoc_print_warning(line_count,
				cmd->rdr.infile[idx].delimiter);
			break ;
		}
		line_count += 1;
		if (strcmp(line, cmd->rdr.infile[idx].delimiter) == 0)
		{
			free(line);
			break ;
		}
		line = heredoc_expansion(envp, line);
		if (line == NULL)
			return (NULL);
		ft_putendl_fd(line, cmd->rdr.infile[idx].fd);
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
static void	*heredoc_create_file(t_cmd *cmd, const t_list *envp)
{
	size_t	i;

	i = 0;
	while (cmd->rdr.infile[i].file)
	{
		if (cmd->rdr.infile[i].redir_type == TYPE_REDIRECTION_HEREDOC)
		{
			cmd->rdr.infile[i].fd = open(cmd->rdr.infile[i].file,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (cmd->rdr.infile[i].fd == -1)
			{
				return (NULL);
			}
			if (heredoc_readline(cmd, envp, i) == NULL)
			{
				return (NULL);
			}
			close(cmd->rdr.infile[i].fd);
			cmd->rdr.infile[i].fd = -1;
		}
		i += 1;
	}
	return (cmd);
}

/**
 * @brief Handle the heredoc redirections.
 */
int	heredoc(t_data *data)
{
	t_cmd	*cmd;

	if (heredoc_init(data->command) == NULL)
	{
		perror("minishell");
		return (FAILURE);
	}
	cmd = data->command;
	while (cmd)
	{
		if (heredoc_create_file(cmd, data->envp) == NULL)
		{
			perror("minishell");
			return (FAILURE);
		}
		cmd = cmd->next;
	}
	return (SUCCESS);
}
