/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:15:39 by dbakker           #+#    #+#             */
/*   Updated: 2025/11/28 10:00:58 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints a warning if a null byte is sent using `CTRL + D`.
 */
void	heredoc_print_warning(size_t line_count, const char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document at line ", STDERR_FILENO);
	ft_putnum_fd(line_count, STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

/**
 * @return The length of @p `line` until it encounters a non-alphanumeric or
 * @return underscore character.
 */
size_t	heredoc_variable_length(const char *line)
{
	size_t	length;

	length = 0;
	while (ft_isalnum(line[length]) || line[length] == '_')
	{
		length += 1;
	}
	return (length);
}

/**
 * @brief Duplicates the first variable found in @p `line`.
 *
 * @param[in] line The line read.
 *
 * @return Pointer to duplicated variable, or `NULL` on failure.
 *
 * @warning Caller owns `free()`.
 */
char	*heredoc_duplicate(const char *line)
{
	char	*dollar;
	size_t	num;

	dollar = ft_strchr(line, '$') + 1;
	num = heredoc_variable_length(dollar);
	return (ft_strndup(dollar, num));
}

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
