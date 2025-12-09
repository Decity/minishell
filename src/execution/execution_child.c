/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 10:30:00 by elie              #+#    #+#             */
/*   Updated: 2025/12/08 10:18:46 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_other_cmd_fds(t_data *data, t_cmd *current_cmd)
{
	t_cmd	*other_cmd;

	other_cmd = data->command;
	while (other_cmd)
	{
		if (other_cmd != current_cmd)
		{
			if (other_cmd->rdr.i_fd != STDIN_FILENO
				&& other_cmd->rdr.i_fd != -1)
				close(other_cmd->rdr.i_fd);
			if (other_cmd->rdr.o_fd != STDOUT_FILENO
				&& other_cmd->rdr.o_fd != -1)
				close(other_cmd->rdr.o_fd);
		}
		other_cmd = other_cmd->next;
	}
}

void	execute_child(t_cmd *cmd, t_data *data)
{
	restore_signals_default();
	if (apply_redirections(cmd) == FAILURE)
		exit_cleanup(data, 1);
	if (!cmd->args[0])
		exit_cleanup(data, 0);
	if (is_builtin(cmd->args[0]))
		exit_cleanup(data, execute_builtin(cmd, data));
	else
		execute_binary(cmd, data);
}

void	exec_pipeline_child(t_cmd *cmd, t_data *data, t_pnp *pnp, bool is_first)
{
	restore_signals_default();
	setup_child_redirections(pnp->pipefd, pnp->prev_pipefd, is_first,
		cmd->next == NULL);
	close_pipes(pnp->pipefd, pnp->prev_pipefd, is_first, !cmd->next);
	free(pnp->pipefd);
	close_other_cmd_fds(data, cmd);
	if (apply_redirections(cmd) == FAILURE)
		exit_cleanup(data, 1);
	if (!cmd->args[0])
		exit_cleanup(data, 0);
	if (is_builtin(cmd->args[0]))
		exit_cleanup(data, execute_builtin(cmd, data));
	else
		execute_binary(cmd, data);
}
