/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:02:01 by ebelle            #+#    #+#             */
/*   Updated: 2025/10/03 13:39:49 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

void	execute(t_data *data)
{
	pid_t	pid;
	int		fd;

	if (DEBUG)
		printf("=== execute_command() ===\n\n");

	pid = fork();
	if (pid == 0)
	{
		// Child process
		fd = open(data->command->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);

		execve("/usr/bin/ls", &data->command->arguments[0], data->command->arguments);
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

