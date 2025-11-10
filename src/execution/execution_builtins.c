/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:22:00 by elie              #+#    #+#             */
/*   Updated: 2025/11/10 15:00:16 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	execute_builtin(t_cmd *cmd, t_data *data)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		ed_echo((const char **)cmd->args + 1);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		ed_change_directory(data->envp, &data->directory, cmd->args[1]);
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		pwd_print(data->directory);
	if (ft_strcmp(cmd->args[0], "export") == 0)
	{
		if (cmd->args[1])
			export_env(data->envp, cmd->args[1]);
		else
			export_print(data->envp);
	}
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		unset_env(&data->envp, cmd->args[1]);
	if (ft_strcmp(cmd->args[0], "env") == 0)
		env_print(data->envp);
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		minishell_exit(data);
}

void	execute_single_builtin(t_cmd *cmd, t_data *data)
{
	int		saved_stdin;
	int		saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	apply_redirections(cmd);
	execute_builtin(cmd, data);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}
