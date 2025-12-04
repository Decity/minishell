/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipeline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:25:00 by elie              #+#    #+#             */
/*   Updated: 2025/12/04 16:30:54 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_pipeline_child(t_cmd *cmd, t_data *data, int *pipefd, int prev_pipefd, bool is_first, bool is_last)
{
	restore_signals_default();
	setup_child_redirections(pipefd, prev_pipefd, is_first, is_last);
	close_pipes(pipefd, prev_pipefd, is_first, is_last);
	execute_single_cmd(cmd, data);
	data->exit_status = 1;
	free(pipefd);
	exit_cleanup(data);
	exit(data->exit_status);
}

static void	wait_for_children(pid_t *pids, size_t count, t_data *data)
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

static void	cleanup_pipeline(pid_t *pids, size_t count)
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

void	execute_cmds(t_data *data)
{
	t_cmd	*current;
	pid_t	*pids;
	int		*pipefd;
	int		prev_pipefd;
	size_t	i;

	pids = malloc(get_cmds_count(data->command) * sizeof(pid_t));
	if (pids == NULL)
	{
		perror("minishell: malloc");
		data->exit_status = 1;
		exit_cleanup(data);
		exit(data->exit_status);
	}
	pipefd = malloc(2 * sizeof(int));
	if (pipefd == NULL)
	{
		free(pids);
		perror("minishell: malloc");
		data->exit_status = 1;
		exit_cleanup(data);
		exit(data->exit_status);
	}
	current = data->command;
	i = 0;
	while (current)
	{
		if (current->next != NULL && pipe(pipefd) == -1)
		{
			perror("minishell: pipe");
			data->exit_status = 1;
			cleanup_pipeline(pids, i);
			free(pipefd);
			exit_cleanup(data);
			exit(data->exit_status);
		}
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("minishell: fork");
			data->exit_status = 1;
			cleanup_pipeline(pids, i);
			free(pipefd);
			exit_cleanup(data);
			exit(data->exit_status);
		}
		if (pids[i] == 0)
		{
			free(pids);
			execute_pipeline_child(current, data, pipefd, prev_pipefd, i == 0, current->next == NULL);
		}
		if (i > 0)
			close(prev_pipefd);
		if (current->next != NULL)
		{
			prev_pipefd = pipefd[0];
			close(pipefd[1]);
		}
		current = current->next;
		i++;
	}
	free(pipefd);
	wait_for_children(pids, get_cmds_count(data->command), data);
}
