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

void	exec_pipeline_child(t_cmd *cmd, t_data *data, int *pipefd,
	int prev_pipefd, bool is_first, bool is_last)
{
	restore_signals_default();
	setup_child_redirections(pipefd, prev_pipefd, is_first, is_last);
	close_pipes(pipefd, prev_pipefd, is_first, is_last);
	free(pipefd);
	if (apply_redirections(cmd) == FAILURE)
		exit_cleanup(data, 1);
	if (!cmd->args[0])
		exit_cleanup(data, 0);
	if (is_builtin(cmd->args[0]))
		exit_cleanup(data, execute_builtin(cmd, data));
	else
		execute_binary(cmd, data);
}
