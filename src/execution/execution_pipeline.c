/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipeline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:25:00 by elie              #+#    #+#             */
/*   Updated: 2025/12/08 10:19:40 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipeline(t_data *data, pid_t **pids, int **pipefd)
{
	*pids = malloc(get_cmds_count(data->command) * sizeof(pid_t));
	if (*pids == NULL)
	{
		perror("minishell: malloc");
		exit_cleanup(data, 1);
	}
	*pipefd = malloc(2 * sizeof(int));
	if (*pipefd == NULL)
	{
		free(*pids);
		perror("minishell: malloc");
		exit_cleanup(data, 1);
	}
}

void	handle_pipe_creation(t_cmd *current, int *pipefd, pid_t *pids,
	t_data *data, size_t i)
{
	if (current->next != NULL && pipe(pipefd) == -1)
	{
		perror("minishell: pipe");
		cleanup_pipeline(pids, i);
		free(pipefd);
		exit_cleanup(data, 1);
	}
}

void	fork_and_execute(t_cmd *current, pid_t *pids, int *pipefd,
	int prev_pipefd, size_t i, t_data *data)
{
	pids[i] = fork();
	if (pids[i] == -1)
		handle_fork_error(pids, i, pipefd, data);
	if (pids[i] == 0)
	{
		free(pids);
		exec_pipeline_child(current, data, pipefd, prev_pipefd, i == 0,
			current->next == NULL);
	}
}

void	handle_pipeline(t_data *data)
{
	t_cmd	*current;
	pid_t	*pids;
	int		*pipefd;
	int		prev_pipefd;
	size_t	i;

	init_pipeline(data, &pids, &pipefd);
	current = data->command;
	i = 0;
	while (current)
	{
		handle_pipe_creation(current, pipefd, pids, data, i);
		fork_and_execute(current, pids, pipefd, prev_pipefd, i, data);
		close_parent_pipes(i, prev_pipefd, pipefd, current);
		if (current->next != NULL)
			prev_pipefd = pipefd[0];
		current = current->next;
		i++;
	}
	free(pipefd);
	wait_for_children(pids, get_cmds_count(data->command), data);
}
