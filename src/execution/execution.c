/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:02:01 by ebelle            #+#    #+#             */
/*   Updated: 2025/11/10 15:41:04 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Execute parsed command(s)
 *
 * Determines execution mode (single builtin, single command, or pipeline)
 * and dispatches to appropriate handler. Manages signal handlers.
 *
 * @param[in,out] data Shell data structure with parsed commands
 */
void	execution(t_data *data)
{
	if (data->is_interactive)
		setup_signals_executing();

	// execution mode
	if (!data->command->next && is_builtin(data->command->args[0]))
		execute_single_builtin(data->command, data);
	else if (!data->command->next)
		execute_single_cmd(data->command, data);
	else
		execute_cmds(data);

	if (data->is_interactive)
		setup_signals_interactive();
}

/**
 * @brief Execute a single command in a child process
 *
 * Forks a child process, applies redirections, executes the command
 * (builtin or binary), and waits for completion.
 *
 * @param[in] cmd Command to execute
 * @param[in,out] data Shell data structure
 */
void	execute_single_cmd(t_cmd *cmd, t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	// handle error
	if (pid == 0)
	{
		restore_signals_default();
		apply_redirections(cmd);
		if (is_builtin(cmd->args[0]))
			execute_builtin(cmd, data);
		else
			execute_binary(cmd, data->envp);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
}

/**
 * @brief Execute a binary program
 *
 * Determines executable path (absolute, relative, or PATH search),
 * converts environment list to array, and calls execve.
 *
 * @param[in] cmd Command to execute
 * @param[in] envp Environment variables list
 */
void	execute_binary(t_cmd *cmd, t_list *envp)
{
	char	*path;

	if (cmd->args[0][0] == '/' || ft_strncmp(cmd->args[0], "./", 2) == 0 || ft_strncmp(cmd->args[0], "../", 3) == 0)
		path = cmd->args[0];
	else
		path = get_executable_path(cmd->args[0], envp);
	// handle error
	execve(path, cmd->args, llist_to_array(envp));
	exit(1);
}
