/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:56:00 by elie              #+#    #+#             */
/*   Updated: 2025/11/10 15:00:25 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Find executable path by searching PATH directories
 *
 * Searches directories in PATH environment variable for the executable.
 *
 * @param[in] exec Executable name
 * @param[in] envp Environment variables list
 *
 * @return Path to executable, or NULL if not found
 */
char	*get_executable_path(const char *exec, const t_list *envp)
{
	char	**paths;
	char	*abs_path;
	char	*slashed_path;
	size_t	i;

	paths = ft_split(ft_getenv(envp, "PATH"), ':');
	// TODO: Handle malloc fail.
	i = 0;
	while (paths[i])
	{
		slashed_path = ft_strjoin(paths[i], "/");
		abs_path = ft_strjoin(slashed_path, exec);
		// TODO: handle malloc fail.
		free(slashed_path);
		if (access(abs_path, X_OK) == 0)
		{
			return (abs_path);
		}
		free(abs_path);
		i++;
	}
	return (NULL);
}

/**
 * @brief Count number of commands in linked list
 *
 * @param[in] commands Head of command list
 *
 * @return Number of commands
 */
size_t	get_cmds_count(t_cmd *commands)
{
	size_t	count;
	t_cmd	*current;

	count = 0;
	current = commands;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

/**
 * @brief Close pipe file descriptors
 *
 * Closes previous pipe read end and current pipe both ends if applicable.
 *
 * @param[in] pipefd Current pipe file descriptors
 * @param[in] prev_pipefd Previous pipe read end
 * @param[in] is_first True if first command in pipeline
 * @param[in] is_last True if last command in pipeline
 */
void	close_pipes(int *pipefd, int prev_pipefd, bool is_first, bool is_last)
{
	if (!is_first)
		close(prev_pipefd);

	if (!is_last)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}

}

/**
 * @brief Set up stdin/stdout for pipeline child process
 *
 * Duplicates pipe file descriptors to stdin/stdout as needed.
 *
 * @param[in] pipefd Current pipe file descriptors
 * @param[in] prev_pipefd Previous pipe read end
 * @param[in] is_first True if first command in pipeline
 * @param[in] is_last True if last command in pipeline
 */
void	setup_child_redirections(int *pipefd, int prev_pipefd, bool is_first, bool is_last)
{
	if (!is_first)
		dup2(prev_pipefd, STDIN_FILENO);
	if (!is_last)
		dup2(pipefd[1], STDOUT_FILENO);
}

/**
 * @brief Apply file redirections to stdin/stdout
 *
 * Redirects stdin/stdout to specified file descriptors if set.
 *
 * @param[in] cmd Command with redirection info
 */
void	apply_redirections(t_cmd *cmd)
{
	// Input redirect overrides pipe input
	if (cmd->redirect.input_fd != STDIN_FILENO && cmd->redirect.input_fd != -1)
	{
		dup2(cmd->redirect.input_fd, STDIN_FILENO);
		close(cmd->redirect.input_fd);
	}

	// Output redirect overrides pipe output
	if (cmd->redirect.output_fd != STDOUT_FILENO && cmd->redirect.output_fd != -1)
	{
		dup2(cmd->redirect.output_fd, STDOUT_FILENO);
		close(cmd->redirect.output_fd);
	}
}