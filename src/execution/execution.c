/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:02:01 by ebelle            #+#    #+#             */
/*   Updated: 2025/12/05 10:30:00 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(const char *cmd)
{
	if (!cmd)
		return (false);
	if (ft_strcmp(cmd, "echo") == 0)
		return (true);
	if (ft_strcmp(cmd, "cd") == 0)
		return (true);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd, "export") == 0)
		return (true);
	if (ft_strcmp(cmd, "unset") == 0)
		return (true);
	if (ft_strcmp(cmd, "env") == 0)
		return (true);
	if (ft_strcmp(cmd, "exit") == 0)
		return (true);
	return (false);
}

void	execution(t_data *data)
{
	if (data->is_interactive)
		setup_signals_executing();
	if (!data->command->next && is_builtin(data->command->args[0]))
		handle_single_builtin(data->command, data);
	else if (!data->command->next)
		handle_single_cmd(data->command, data);
	else
		handle_pipeline(data);
	if (data->is_interactive)
		setup_signals_interactive();
}

void	handle_single_cmd(t_cmd *cmd, t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		data->exit_status = 1;
		return ;
	}
	if (pid == 0)
		execute_child(cmd, data);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->exit_status = 128 + WTERMSIG(status);
}
