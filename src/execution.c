/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:02:01 by ebelle            #+#    #+#             */
/*   Updated: 2025/10/07 14:19:19 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
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
 * @return Path to the binary, or NULL if not found.
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
	int		fd;

	if (DEBUG)
		printf("=== execute_command() ===\n\n");

	path = get_executable_path(data->command->arguments[0]);
	if (path == NULL)
	{
		printf("NULL\n");
		return ;
	}
	printf("%s\n", path);
	pid = fork();
	if (pid == 0)
	{
		// Child process
		fd = open(data->command->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);

		execve(path, &data->command->arguments[0], data->command->arguments);
		// execvp(data->command->arguments[0], data->command->arguments);
	}
	else
	{
		// Parent process
		wait(NULL);
	}

	// clean up data->input, data->tokens, and data->command
	cleanup_data(data);
}

