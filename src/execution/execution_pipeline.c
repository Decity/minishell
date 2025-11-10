/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipeline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:25:00 by elie              #+#    #+#             */
/*   Updated: 2025/11/05 15:38:17 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <sys/wait.h>
#include <unistd.h>

void	execute_pipeline_child(t_cmd *cmd, t_data *data, int *pipefd, int prev_pipefd, bool is_first, bool is_last)
{
	restore_signals_default();
	setup_child_redirections(pipefd, prev_pipefd, is_first, is_last);
	close_pipes(pipefd, prev_pipefd, is_first, is_last);
	execute_single_cmd(cmd, data);
	exit(1);
}

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
		}
		i++;
	}
}

void	execute_cmds(t_data *data)
{
	t_cmd	*current;
	pid_t	*pids;
	int		*pipefd;
	int		prev_pipefd;
	size_t	i;

	pids = malloc(get_cmds_count(data->command) * sizeof(pid_t));
	// handle error
	pipefd = malloc (2 * sizeof(int));
	// handle error
	current = data->command;
	i = 0;
	while (current)
	{
		if (current->next != NULL)
		{
			pipe(pipefd);
			// handle error
		}

		pids[i] = fork();
		// handle error
		if (pids[i] == 0)
			execute_pipeline_child(current, data, pipefd, prev_pipefd, i == 0, current->next == NULL);

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
	wait_for_children(pids, get_cmds_count(data->command), data);
}
