/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipeline_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 10:30:00 by elie              #+#    #+#             */
/*   Updated: 2025/12/09 14:33:43 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_children(pid_t *pids, size_t count, t_data *data)
{
	size_t	i;
	int		status;

	i = 0;
	while (i < count)
	{
		waitpid(pids[i], &status, 0);
		if (i == count - 1)
		{
			if (WIFEXITED(status))
				data->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	free(pids);
}

void	cleanup_pipeline(pid_t *pids, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		if (pids[i] > 0)
			kill(pids[i], SIGKILL);
		i++;
	}
	free(pids);
}

void	handle_fork_error(pid_t *pids, size_t i, int *pipefd, t_data *data)
{
	perror("minishell: fork");
	cleanup_pipeline(pids, i);
	free(pipefd);
	exit_cleanup(data, 1);
}

void	close_parent_pipes(size_t i, int prev_pipefd, int *pipefd,
	t_cmd *current)
{
	if (i > 0)
		close(prev_pipefd);
	if (current->next != NULL)
		close(pipefd[1]);
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
