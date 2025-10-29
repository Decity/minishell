/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:02:01 by ebelle            #+#    #+#             */
/*   Updated: 2025/10/29 11:40:42 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

/**
 * @brief Return the absolute path for @p `exec` from the PATH environment.
 *
 * It will additionally verify if @p `exec` has execution rights.
 *
 * @param[in] exec The binary to find.
 *
 * @return Path to the binary, or `NULL` if not found.
 */
char	*get_executable_path(const char *exec)
{
	char	**paths;
	char	*abs_path;
	char	*slashed_path;
	size_t	i;

	paths = ft_split(getenv("PATH"), ':');
	// TODO: Handle malloc fail.
	i = 0;
	while (paths[i])
	{
		slashed_path = ft_strjoin(paths[i], "/");
		abs_path = ft_strjoin(slashed_path, exec);
		// TODO: handle malloc fail.
		free(slashed_path);
		if (access(abs_path, X_OK) == 0)
		{
			return (abs_path);
		}
		free(abs_path);
		i++;
	}
	return (NULL);
}

void	execute(t_data *data)
{
	pid_t	pid;
	char	*path;

	if (DEBUG)
		printf("=== execute_command() ===\n\n");

	path = get_executable_path(data->command->args[0]);
	pid = fork();
	if (pid == 0)
	{
		// Child process
		dup2(data->command->redirect.input_fd, STDIN_FILENO);
		dup2(data->command->redirect.output_fd, STDOUT_FILENO);

		execve(path, data->command->args, llist_to_array(data->envp));
	}
	else
	{
		// Parent process
		wait(NULL);
		if (data->command->redirect.infile)
			close(data->command->redirect.input_fd);
		if (data->command->redirect.outfile)
			close(data->command->redirect.output_fd);
	}
}
