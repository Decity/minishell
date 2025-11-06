/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:02:01 by ebelle            #+#    #+#             */
/*   Updated: 2025/11/06 10:38:23 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

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

void	execute_single_cmd(t_cmd *cmd, t_data *data)
{
	char	**envp;
	pid_t	pid;
	int		status;

	envp = llist_to_array(data->envp);
	pid = fork();
	// handle error
	if (pid == 0)
	{
		restore_signals_default();
		apply_redirections(cmd);
		if (is_builtin(cmd->args[0]))
			execute_builtin(cmd, data);
		else
			execute_binary(cmd, envp);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
}

void	execute_binary(t_cmd *cmd, char **envp)
{
	char	*path;

	path = get_executable_path(cmd->args[0]);
	// handle error
	execve(path, cmd->args, envp);
	exit(1);
}
