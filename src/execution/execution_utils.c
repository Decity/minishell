/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:56:00 by elie              #+#    #+#             */
/*   Updated: 2025/12/09 16:52:11 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_bin_paths(const t_list *envp)
{
	char	**paths;
	char	*path_env;

	path_env = ft_getenv(envp, "PATH");
	if (path_env == NULL)
		return (NULL);
	paths = ft_split(path_env, ':');
	return (paths);
}

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

	paths = get_bin_paths(envp);
	if (paths == NULL)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		slashed_path = ft_strjoin(paths[i], "/");
		if (slashed_path == NULL)
			return (perror("minishell"), free_array(&paths), NULL);
		abs_path = ft_strjoin(slashed_path, exec);
		free(slashed_path);
		if (abs_path == NULL)
			return (perror("minishell"), free_array(&paths), NULL);
		if (access(abs_path, X_OK) == 0)
			return (free_array(&paths), abs_path);
		free(abs_path);
		i++;
	}
	return (free_array(&paths), NULL);
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
 * @brief Set up stdin/stdout for pipeline child process
 *
 * Duplicates pipe file descriptors to stdin/stdout as needed.
 *
 * @param[in] pipefd Current pipe file descriptors
 * @param[in] prev_pipefd Previous pipe read end
 * @param[in] is_first True if first command in pipeline
 * @param[in] is_last True if last command in pipeline
 */
void	setup_child_redirections(int *pipefd, int prev_pipefd, bool is_first,
	bool is_last)
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
 * @return SUCCESS on success, FAILURE on dup2 failure
 */
int	apply_redirections(t_cmd *cmd)
{
	if (cmd->rdr.i_fd != STDIN_FILENO && cmd->rdr.i_fd != -1)
	{
		if (dup2(cmd->rdr.i_fd, STDIN_FILENO) == -1)
		{
			perror("minishell: dup2");
			return (FAILURE);
		}
		close(cmd->rdr.i_fd);
		cmd->rdr.i_fd = -1;
	}
	if (cmd->rdr.o_fd != STDOUT_FILENO
		&& cmd->rdr.o_fd != -1)
	{
		if (dup2(cmd->rdr.o_fd, STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2");
			return (FAILURE);
		}
		close(cmd->rdr.o_fd);
		cmd->rdr.o_fd = -1;
	}
	return (SUCCESS);
}
