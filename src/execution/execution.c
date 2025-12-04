/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:02:01 by ebelle            #+#    #+#             */
/*   Updated: 2025/12/02 13:18:39 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

static void	execute_binary(t_cmd *cmd, t_data *data);

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
	if (pid == -1)
	{
		perror("minishell: fork");
		data->exit_status = 1;
		exit_cleanup(data);
		exit(data->exit_status);
	}
	if (pid == 0)
	{
		restore_signals_default();
		if (apply_redirections(cmd) == FAILURE)
		{
			data->exit_status = 1;
			exit(data->exit_status);
		}
		if (is_builtin(cmd->args[0]))
		{
			data->exit_status = execute_builtin(cmd, data);
			exit(data->exit_status);
		}
		else
			execute_binary(cmd, data);
		data->exit_status = 1;
		exit(data->exit_status);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->exit_status = 128 + WTERMSIG(status);
}

/**
 * @brief Execute a binary program
 *
 * Determines executable path (absolute, relative, or PATH search),
 * converts environment list to array, and calls execve.
 * Exits with appropriate error codes if execution fails.
 *
 * @param[in] cmd Command to execute
 * @param[in,out] data Shell data structure
 */
static void	execute_binary(t_cmd *cmd, t_data *data)
{
	char	*path;

	if (cmd->args[0][0] == '/' || ft_strncmp(cmd->args[0], "./", 2) == 0 || ft_strncmp(cmd->args[0], "../", 3) == 0)
		path = cmd->args[0];
	else
	{
		path = get_executable_path(cmd->args[0], data->envp);
		if (path == NULL)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd->args[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			data->exit_status = 127;
			exit(data->exit_status);
		}
	}
	execve(path, cmd->args, llist_to_array(data->envp));
	perror("minishell");
	if (errno == ENOENT)
		data->exit_status = 127;
	else if (errno == EACCES)
		data->exit_status = 126;
	else
		data->exit_status = 1;
	exit(data->exit_status);
}
