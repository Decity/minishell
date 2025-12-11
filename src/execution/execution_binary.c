/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_binary.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 10:30:00 by elie              #+#    #+#             */
/*   Updated: 2025/12/11 14:42:53 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

char	*get_bin_path(t_cmd *cmd, t_data *data)
{
	char	*path;

	if (cmd->args[0][0] == '/'
		|| ft_strncmp(cmd->args[0], "./", 2) == 0
		|| ft_strncmp(cmd->args[0], "../", 3) == 0)
		return (cmd->args[0]);
	path = get_executable_path(cmd->args[0], data->envp);
	if (path == NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit_cleanup(data, 127);
	}
	return (path);
}

void	execute_binary(t_cmd *cmd, t_data *data)
{
	char	*path;
	int		exit_code;

	path = get_bin_path(cmd, data);
	execve(path, cmd->args, llist_to_array(data->envp));
	exit_code = 1;
	perror("minishell");
	if (errno == ENOENT)
		exit_code = 127;
	else if (errno == EACCES || errno == ENOTDIR)
		exit_code = 126;
	exit_cleanup(data, exit_code);
}
