/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipeline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:25:00 by elie              #+#    #+#             */
/*   Updated: 2025/12/14 16:48:51 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipeline(t_data *data, t_pnp *pnp)
{
	pnp->pids = malloc(get_cmds_count(data->command) * sizeof(pid_t));
	if (pnp->pids == NULL)
	{
		perror("minishell: malloc");
		exit_cleanup(data, 1);
	}
	pnp->pipefd = malloc(2 * sizeof(int));
	if (pnp->pipefd == NULL)
	{
		free(pnp->pids);
		perror("minishell: malloc");
		exit_cleanup(data, 1);
	}
}

void	handle_pipe_creation(t_cmd *current, t_pnp *pnp, t_data *data, size_t i)
{
	if (current->next != NULL && pipe(pnp->pipefd) == -1)
	{
		perror("minishell: pipe");
		cleanup_pipeline(pnp->pids, i);
		free(pnp->pipefd);
		exit_cleanup(data, 1);
	}
}

void	fork_and_execute(t_cmd *current, t_pnp *pnp, size_t i, t_data *data)
{
	pnp->pids[i] = fork();
	if (pnp->pids[i] == -1)
		handle_fork_error(pnp->pids, i, pnp->pipefd, data);
	if (pnp->pids[i] == 0)
	{
		close_redirection_fds(data);
		free(pnp->pids);
		exec_pipeline_child(current, data, pnp, i == 0);
	}
}

void	handle_pipeline(t_data *data)
{
	t_cmd	*current;
	t_pnp	pnp;
	size_t	i;

	ft_memset(&pnp, 0, sizeof(t_pnp));
	init_pipeline(data, &pnp);
	current = data->command;
	i = 0;
	while (current)
	{
		handle_pipe_creation(current, &pnp, data, i);
		fork_and_execute(current, &pnp, i, data);
		close_parent_pipes(i, pnp.prev_pipefd, pnp.pipefd, current);
		if (current->next != NULL)
			pnp.prev_pipefd = pnp.pipefd[0];
		current = current->next;
		i++;
	}
	free(pnp.pipefd);
	wait_for_children(pnp.pids, get_cmds_count(data->command), data);
}
