/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_binary.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 10:30:00 by elie              #+#    #+#             */
/*   Updated: 2025/12/11 18:44:45 by dbakker          ###   ########.fr       */
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
		return (NULL);
	}
	return (path);
}

void	execute_binary(t_cmd *cmd, t_data *data)
{
	char	**array;
	char	*path;
	int		exit_code;

	array = llist_to_array(data->envp);
	path = get_bin_path(cmd, data);
	if (path == NULL)
	{
		free_array(&array);
		exit_cleanup(data, 127);
	}
	execve(path, cmd->args, array);
	free_array(&array);
	exit_code = 1;
	perror("minishell");
	if (errno == ENOENT)
		exit_code = 127;
	else if (errno == EACCES || errno == ENOTDIR)
		exit_code = 126;
	exit_cleanup(data, exit_code);
}
