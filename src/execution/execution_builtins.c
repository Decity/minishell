/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:22:00 by elie              #+#    #+#             */
/*   Updated: 2025/11/29 20:48:48 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Check if command is a shell builtin
 *
 * @param[in] cmd Command name
 *
 * @return True if builtin, false otherwise
 */
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

/**
 * @brief Execute a builtin command
 *
 * Dispatches to appropriate builtin handler based on command name.
 *
 * @param[in] cmd Command to execute
 * @param[in,out] data Shell data structure
 */
void	execute_builtin(t_cmd *cmd, t_data *data)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		builtin_echo((const char **)cmd->args + 1);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		builtin_cd(data->envp, &data->directory, cmd->args[1]);
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		pwd_print(data->directory);
	if (ft_strcmp(cmd->args[0], "export") == 0)
	{
		if (cmd->args[1])
			builtin_export(data->envp, cmd->args[1]);
		else
			export_print(data->envp);
	}
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		builtin_unset(&data->envp, cmd->args[1]);
	if (ft_strcmp(cmd->args[0], "env") == 0)
		builtin_env_print(data->envp);
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		minishell_exit(data);
}

/**
 * @brief Execute a single builtin with redirections
 *
 * Saves stdin/stdout, applies redirections, executes builtin, then restores.
 *
 * @param[in] cmd Command to execute
 * @param[in,out] data Shell data structure
 */
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
