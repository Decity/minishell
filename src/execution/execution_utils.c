/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:56:00 by elie              #+#    #+#             */
/*   Updated: 2025/10/28 14:22:17 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <unistd.h>

char	*get_executable_path(const char *exec)
{
	char	**paths;
	char	*abs_path;
	char	*slashed_path;
	size_t	i;

	paths = ft_split(getenv("PATH"), ':');
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

void	setup_child_redirections(int *pipefd, int prev_pipefd, bool is_first, bool is_last)
{
	if (!is_first)
		dup2(prev_pipefd, STDIN_FILENO);
	if (!is_last)
		dup2(pipefd[1], STDOUT_FILENO);
}

void	apply_redirections(t_cmd *cmd)
{
	// Input redirection overrides pipe input
	if (cmd->redirection.input_fd != STDIN_FILENO && cmd->redirection.input_fd != -1)
	{
		dup2(cmd->redirection.input_fd, STDIN_FILENO);
		close(cmd->redirection.input_fd);
	}

	// Output redirection overrides pipe output
	if (cmd->redirection.output_fd != STDOUT_FILENO && cmd->redirection.output_fd != -1)
	{
		dup2(cmd->redirection.output_fd, STDOUT_FILENO);
		close(cmd->redirection.output_fd);
	}
}