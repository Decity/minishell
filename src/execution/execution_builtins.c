/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:22:00 by elie              #+#    #+#             */
/*   Updated: 2025/12/08 14:44:27 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_export(t_cmd *cmd, t_data *data);
static void	handle_redir_error(int saved_stdin, int saved_stdout, t_data *data);

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

int	execute_builtin(t_cmd *cmd, t_data *data)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (builtin_echo((const char **)cmd->args + 1));
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (builtin_cd(data->envp, &data->directory, cmd->args[1]));
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (pwd_print(data->directory));
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (handle_export(cmd, data));
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (builtin_unset(&data->envp, cmd->args[1]));
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (builtin_env_print(data->envp));
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		minishell_exit(data);
	return (0);
}

static int	handle_export(t_cmd *cmd, t_data *data)
{
	if (cmd->args[1])
	{
		if (builtin_export(data->envp, cmd->args[1]) == NULL)
			return (1);
		return (0);
	}
	else
		return (export_print(data->envp));
}

void	handle_single_builtin(t_cmd *cmd, t_data *data)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
	{
		handle_redir_error(saved_stdin, saved_stdout, data);
		return ;
	}
	if (apply_redirections(cmd) == FAILURE)
	{
		close(saved_stdin);
		close(saved_stdout);
		data->exit_status = 1;
		return ;
	}
	if (ft_strcmp(cmd->args[0], "exit") == 0)
	{
		close(saved_stdin);
		close(saved_stdout);
	}
	data->exit_status = execute_builtin(cmd, data);
	if (ft_strcmp(cmd->args[0], "exit") != 0)
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
	}
}

static void	handle_redir_error(int saved_stdin, int saved_stdout, t_data *data)
{
	perror("minishell: dup");
	if (saved_stdin != -1)
		close(saved_stdin);
	if (saved_stdout != -1)
		close(saved_stdout);
	data->exit_status = 1;
}
